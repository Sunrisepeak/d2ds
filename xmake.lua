add_rules("mode.debug")

set_languages("cxx11")
add_includedirs(".")

-- verify lib
add_includedirs("DStruct")

target("0.dslings-0")
    set_kind("binary")
    add_files("tests/dslings.0.cpp")

target("0.dslings-1")
    set_kind("binary")
    add_files("tests/dslings.1.cpp")

target("0.dslings-2")
    set_kind("binary")
    add_files("tests/dslings.2.cpp")

target("1.array-0")
    set_kind("binary")
    add_files("tests/array/array.0.cpp")

target("1.array-1")
    set_kind("binary")
    add_files("tests/array/array.1.cpp")

-- dslings: auto checker and update status for exercises
task("dslings")
    on_run(function()
        import("core.project.project")
        import("core.project.target")
        import("core.base.global")

        local function get_len(pairs_type)
            length = 0
            for _, _ in pairs_type do
                length = length + 1
            end
            return length
        end

        local function clear_screen()
            if os.host() == "windows" then
                os.exec("cls")
            else
                os.exec("clear")
            end
        end

        local function print_info(target_name, built_targets, total_targets, current_file_path, output, success)

            clear_screen()

            -- print progress_bar
            local progress_bar_length = total_targets
            local arrow_count = built_targets
            local dash_count = progress_bar_length - arrow_count
            local progress_bar = string.format(
                "🌏Progress: [%s>%s] %d/%d",
                string.rep("=", arrow_count),
                string.rep("-", dash_count),
                arrow_count, progress_bar_length
            )
            print(progress_bar)

            print(string.format("\n[Target: %s]\n", target_name))

            -- print status
            if success then
                print(string.format("✅ Successfully ran %s!", current_file_path))
                print("\n🎉   The code is compiling!   🎉\n")
            else
                print(string.format("❌ Error: Compilation/Running failed for %s:", current_file_path))
                print("\n The code exist some error!\n")
            end

            -- print output
            print("Output:")
            print("====================")
            print(output)
            print("====================")

            print("\nBook: https://sunrisepeak.github.io/d2ds")
        end

        -- main start

        clear_screen()

        local base_dir = os.projectdir()

        -- 获取 project 中所有 target
        local targets = project.targets()
        --local targets = {"d2ds_array", "d2ds_array1"}
        --local total_targets = #targets --
        -- TODO: optimize total_targets
        local total_targets = 0
        local built_targets = 0
        local sorted_targets = {}
        for name, _ in pairs(targets) do
            total_targets = total_targets + 1
            table.insert(sorted_targets, name)
        end

        table.sort(sorted_targets)

        for _, name in pairs(sorted_targets) do
            local files = targets[name]:sourcefiles()
            for  _, file in ipairs((files)) do
                local relative_path = path.relative(file, base_dir)
                local build_success = false
                local sleep_sec = 1000 * 0.1
                local output = ""

                while not build_success do
                    --build_success = task.run("build", {target = name})
                    build_success = true
                    try
                    {
                        function()
                            os.iorunv("xmake", {"build", name})
                            --os.iorunv("xmake", {"build", "-v", name})
                        end,
                        catch
                        {
                            -- After an exception occurs, it is executed
                            function (e)
                                output = e
                                build_success = false
                                sleep_sec = 1000 * 3
                            end
                        }
                    }

                    if build_success then
                        try {
                            function () 
                                output, errs = os.iorunv("xmake", {"r", name})
                            end,
                            catch
                            {
                                function (e)
                                    output = e
                                    build_success = false
                                    sleep_sec = 1000 * 3
                                end
                            }
                        }
                    end

                    if build_success then
                        built_targets = built_targets + 1
                    end

                    print_info(name, built_targets, total_targets, relative_path, output, build_success)
                    output = ""
                    os.sleep(sleep_sec)

                end
            end
        end

        local bingo = "\
            Bingo! 🎉🎉🎉\n \
    You have completed all exercises\n \
MoreInfo: https://github.com/Sunrisepeak/DStruct\
"

        print_info("D2DS", total_targets, total_targets, "...", bingo, true)

    end)
    set_menu({
                usage = "xmake dslings",
                description = "Check and compile files with custom progress output and clear screen.",
                options = {}
            })
