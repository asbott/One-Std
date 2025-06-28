
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeclaration-after-statement"
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
#endif

#define OSTD_IMPL
#define OSTD_HEADLESS
#include "../src/ostd.h"

typedef enum Thread_Task {
	THREAD_TASK_COMPILE,
	THREAD_TASK_RUN
} Thread_Task;

typedef struct Thread_Task_Data {
	string path;
	bool ok;
	Thread thread;
	string log_result;
	f64 total_duration_seconds;
	Thread_Task task;
	u64 oindex;
	Thread *dependency;
} Thread_Task_Data;

unit_local Mutex log_mutex;
unit_local void mutexed_logger(string message, u64 flags, Source_Location location) {
	(void)flags; (void)location;
	sys_mutex_acquire(log_mutex);
	
    prints(message);
    
    if (message.count > 0 && message.data[message.count-1] != '\n') {
        print("\n");
    }
    
	sys_mutex_release(log_mutex);
}

unit_local Thread_Task_Data datas[1024] = {0};
unit_local u64 thread_count = 0;
unit_local u64 file_count = 0;

unit_local s64 file_thread(Thread *t) {
	f64 total_t0 = sys_get_seconds_monotonic();
	u64 index = (u64)t->userdata;
	Thread_Task_Data *data = &datas[index];
	
	if (data->dependency) {
		sys_thread_join(data->dependency);
	}
	
	data->ok = true;
	
	string filename = path_get_filename(data->path);
	string name = path_strip_all_extensions(filename);
	
	string log_file_path = (string){0};
	File_Handle log_file = 0;
	
	if (data->task == THREAD_TASK_COMPILE) {
		f64 compile_t0 = sys_get_seconds_monotonic();
		
		log_file_path = tprint("test_result/%s-compile-O%i.txt", name, data->oindex);
		log_file = sys_open_file(log_file_path, FILE_OPEN_CREATE | FILE_OPEN_RESET | FILE_OPEN_WRITE | FILE_OPEN_READ);
		assertmsgs(log_file, log_file_path);
		
		string compile_args = tprint("\"%s\" -pedantic -nodefaultlibs -Wall -Werror -Weverything -I../vendors -L./../. -DRUNNING_TESTS -DTESTING_DURATION=1", data->path);
	
		string compile_cmd = tprint("clang -o \"test_result/%s-O%i.exe\" %s -O%i -g -DDEBUG -mavx -mavx2", name, data->oindex, compile_args, data->oindex);
		
		fprint(log_file, "\n");
		fprint(log_file, "======================================");
		fprint(log_file, "O%i COMPILE\n", data->oindex);
		fprints(log_file, compile_cmd);
		fprint(log_file, "\n");
		fprint(log_file, "======================================");
		fprint(log_file, "\n");
		Easy_Command_Result res = sys_run_command_easy(compile_cmd, log_file, log_file, STR("./"));
		
		if (res.exit_code != 0) {
			data->ok = false;
		}
		
		f64 compile_t1 = sys_get_seconds_monotonic();
		f64 compile_seconds = compile_t1 - compile_t0;
		
		string spaces = string_allocate(get_temp(), 100);
		for (u64 i = 0; i < spaces.count; i += 1) spaces.data[i] = '-';
		
		string r = data->ok ? STR("\033[32mPASSED\033[0m") : tprint("\033[31mFAILED\033[0m");
		spaces = string_slice(spaces, 0, 40-filename.count);
		log(0, "[%f seconds] %s %s| compile O%i: %s\n", compile_seconds, filename, spaces, data->oindex, r);
		
	} else if (data->task == THREAD_TASK_RUN) {
	
		f64 run_t0 = sys_get_seconds_monotonic();
		
		log_file_path = tprint("test_result/%s-run-O%i.txt", name, data->oindex);
		log_file = sys_open_file(log_file_path, FILE_OPEN_CREATE | FILE_OPEN_RESET | FILE_OPEN_WRITE | FILE_OPEN_READ);
		assertmsgs(log_file, log_file_path);
	
		string run_cmd = tprint("\"test_result/%s-O%i.exe\"", name, data->oindex);
		
		fprint(log_file, "\n");
		fprint(log_file, "======================================");
		fprint(log_file, "O%i RUN\n", data->oindex);
		fprints(log_file, run_cmd);
		fprint(log_file, "\n");
		fprint(log_file, "======================================");
		fprint(log_file, "\n");
		Easy_Command_Result res = sys_run_command_easy(run_cmd, log_file, log_file, STR("../"));
		
		if (res.exit_code != 0) {
			data->ok = false;
		}
		
		f64 run_t1 = sys_get_seconds_monotonic();
		f64 run_seconds = run_t1 - run_t0;
		
		string spaces = string_allocate(get_temp(), 100);
		for (u64 i = 0; i < spaces.count; i += 1) spaces.data[i] = '-';
		
		string r = data->ok ? STR("\033[32mPASSED\033[0m") : tprint("\033[31mFAILED\033[0m");
		spaces = string_slice(spaces, 0, 40-filename.count);
		log(0, "[%f seconds] %s %s| run O%i: %s\n", run_seconds, filename, spaces, data->oindex, r);
	}
	
	
	sys_close(log_file);		
	sys_read_entire_file(get_temp(), log_file_path, &data->log_result);
	
	f64 total_t1 = sys_get_seconds_monotonic();
	
	data->total_duration_seconds = total_t1-total_t0;
	
	return 0;
}

unit_local bool walk_file(string path) {
	
	if (string_ends_with(path, STR(".c")) && !strings_match(path_get_filename(path), STR("run_tests.c"))) {
	
		string pathcp = string_copy(get_temp(), path);
		
		for (u64 i = 0; i < 4; i += 1) {
			datas[thread_count] = (Thread_Task_Data){0};
			datas[thread_count].path = pathcp;
			datas[thread_count].task = THREAD_TASK_COMPILE;
			datas[thread_count].oindex = i;
			sys_thread_init(&datas[thread_count].thread, file_thread, (void*)thread_count);
			thread_count += 1;
			
			datas[thread_count] = (Thread_Task_Data){0};
			datas[thread_count].path = pathcp;
			datas[thread_count].task = THREAD_TASK_RUN;
			datas[thread_count].dependency = &datas[thread_count-1].thread;
			datas[thread_count].oindex = i;
			sys_thread_init(&datas[thread_count].thread, file_thread, (void*)thread_count);
			thread_count += 1;
		}
		
		log(0, "Found c file %s\n", path);
		
		file_count += 1;
		thread_count += 4;
	}	
	
	return true;
}

int main(void) {
	
	sys_mutex_init(&log_mutex);
	logger = mutexed_logger;
	
	string out_dir = STR("test_result");
	
	if (sys_is_directory(out_dir)) {
		sys_remove_directory(out_dir, true);
	}
	bool mkdir_ok = sys_make_directory(out_dir, false);
	assert(mkdir_ok);
	
	if (sys_is_directory(STR("../one-headers"))) {
		sys_remove_directory(STR("../one-headers"), true);
	}
	mkdir_ok = sys_make_directory(STR("../one-headers"), false);
	assert(mkdir_ok);
	
	print("Resolving and testing headers...\n");
	
	f64 headers_t0 = sys_get_seconds_monotonic();
	
	string concat_headers[] = {
		STR("oga_graphics.h"),
		STR("system.h"),
		STR("math.h"),
		STR("string.h"),
		STR("osl_compiler.h"),
		STR("ostd.h"),
		STR("print.h"),
		STR("path_utils.h"),
	};
	
	for (u64 i = 0; i < sizeof(concat_headers)/sizeof(string); i += 1) {
		string header = concat_headers[i];
		
		
		string source_path = tprint("../src/%s", header);
		string out_path = tprint("../one-headers/one_%s", header);
		
		if (strings_match(header, STR("ostd.h"))) {
			out_path = tprint("../ostd_single_header.h");
		}
		
		string concat_cmd = tprint("python ../scripts/concat-header.py \"%s\" \"%s\"", source_path, out_path);
		
		Easy_Command_Result res = sys_run_command_easy(concat_cmd, sys_get_stdout(), sys_get_stdout(), STR("."));
		if (res.exit_code != 0) {
			print("Failed concatenating header %s\n", header);
			return (int)res.exit_code;
		}
		
		string test_path = tprint(
			"#define OSTD_IMPL\n"
			"#ifndef  OSTD_IMPL\n"
			"#endif\n"
			"#include \"../%s\"\n"
			"int main(void) {return 0;}\n"
		, out_path);
		
		sys_write_entire_file(STR("test_result/test.c"), test_path);
		
		string compile_cmd = tprint("clang test_result/test.c -o \"test_result/%s.obj\" -Wall -Weverything -Werror -pedantic -std=c99", header);
		
		res = sys_run_command_easy(compile_cmd, sys_get_stdout(), sys_get_stdout(), STR("."));
		if (res.exit_code != 0) {
			print("Failed compiling header %s\n", header);
			return (int)res.exit_code;
		}
	}
	
	f64 headers_t1 = sys_get_seconds_monotonic();
	
	f64 headers_seconds = headers_t1 - headers_t0;
	
	print("Resolved and compiled headers in %f seconds.\n", headers_seconds);
	
	sys_walk_directory(STR("./"), false, false, walk_file);
	
	f64 t0 = sys_get_seconds_monotonic();
	
	print("Running tests...\n");
	for (u64 i = 0; i < thread_count; i += 1) {
		sys_thread_start(&datas[i].thread);
	}
	for (u64 i = 0; i < thread_count; i += 1) {
		sys_thread_join(&datas[i].thread);
	}
	
	f64 max_duration = 0.0;
	for (u64 i = 0; i < thread_count; i += 1) {
		if (datas[i].total_duration_seconds > max_duration) {
			max_duration = datas[i].total_duration_seconds;
		}
	}
	f64 t1 = sys_get_seconds_monotonic();
	
	
	f64 t = t1-t0;
	
	log(0, "Running all tests took %f seconds\n", t);
	
	log(0, "Goodbye\n");
}
