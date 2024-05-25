add_rules("mode.debug")

set_languages("cxx11")
add_includedirs(".")
add_includedirs("dslings")

-- verify lib
add_includedirs("dstruct")

-- dslings exercises target list
includes("dslings/xmake.lua")

add_moduledirs("common")

task("d2ds")
    on_run("d2ds")
    set_menu {
        usage = "xmake d2ds [command]",
        description = "info | update | help",
        options = {
            {nil, "command", "v", nil, "d2ds's quick command"},
        }
    }

-- dslings: auto checker and update status for exercises
task("dslings")
    on_run("dslings")
    set_menu{
        usage = "xmake dslings [options] [arguments]",
        description = "exercises-code compile-time & runtime checker",
        options = {
            {'s', "start_target", "kv", "0.dslings-0", "check from start_target"},
        }
    }