#!/system/bin/sh
#
# Sample wrapper script that supports using Hardware Address Sanitizer (HWAsan)
# and debugger simultaneously.
#
# This file must be saved using Unix/Linux file endings (NOT Windows),
# otherwise it will fail to execute on Android.

cmd=$1
shift

# Enable support for debugging. Without this, the app will not appear
# debuggable to the clients; i.e., no debugging, no attach-to-process,
# etc.
# Since AGDE only supports HWAsan for Android 14 and newer, the command line
# used here is simpler than the command used in the wrap.sh for ASan (which
# has an if/else chain based on the API level).
cmd="$cmd -XjdwpProvider:adbconnection -XjdwpOptions:suspend=n,server=y $@"

LD_HWASAN=1 exec $cmd