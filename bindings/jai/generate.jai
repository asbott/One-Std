#assert(OS == .WINDOWS);

// Since compile-time debugging is still tricky, it can sometimes be useful to compile this script into a binary and run that instead of generating the bindings at compile-time.
AT_COMPILE_TIME :: true;

#if AT_COMPILE_TIME {
    #run,stallable {
        set_build_options_dc(.{do_output=false});
        if !generate_all_bindings() {
            compiler_set_workspace_status(.FAILED);
        }
    }
} else {
    #import "System";

    main :: () {
        set_working_directory(path_strip_filename(get_path_of_running_executable()));
        if !generate_all_bindings() {
            exit(1);
        }
    }
}

generate_all_bindings :: () -> bool {
    opts: Generate_Bindings_Options;
    array_add(*opts.source_files, "../../src/ostd.h");
    array_add(*opts.libnames, "ostd_windows.dll");
    opts.visitor = ostd_visitor;
    array_add(*opts.extra_clang_arguments, "-Wno-unknown-warning-option");
    return generate_bindings(opts, "ostd_windows.jai");
}

#scope_file

ostd_visitor :: (decl: *Declaration, parent_decl: *Declaration) -> Declaration_Visit_Result {

    if (decl.kind == .STRUCT || decl.kind == .ENUM) && decl.output_name.count > 2 && decl.output_name[0] == #char "_" && decl.output_name[1] !=  #char "_" {
        advance(*decl.output_name);
    }
    
    if decl.kind == .STRUCT && decl.output_name == "string" {
        decl.decl_flags |= .OMIT_FROM_OUTPUT;
        return .STOP;
    }
    
    if decl.output_name == "bool" {
        decl.decl_flags |= .OMIT_FROM_OUTPUT;
        return .STOP;
    }

    return .RECURSE;
}

#import "Basic";
#import "Bindings_Generator";
#import "Compiler";
#import "File";
#import "String";

