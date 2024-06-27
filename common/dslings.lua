import("core.project.project")
import("core.project.target")
import("core.base.global")
import("core.base.option")

-- TODO: optimze
target_to_code_file = {
    ["0.dslings-0"]     = "dslings/exercises/dslings.hpp",
    ["0.dslings-1"]     = "dslings/exercises/dslings.hpp",
    ["0.dslings-2"]     = "dslings/exercises/dslings.hpp",
    ["1.template-0"]    = "dslings/exercises/other/cpp-base/Template.hpp",
    ["1.template-1"]    = "dslings/exercises/other/cpp-base/Template.hpp",
    ["1.template-2"]    = "dslings/exercises/other/cpp-base/Template.hpp",
    ["2.range_for-0"]   = "dslings/exercises/other/cpp-base/RangeFor.hpp",
    ["2.range_for-1"]   = "dslings/exercises/other/cpp-base/RangeFor.hpp",
    ["2.range_for-2"]   = "dslings/exercises/other/cpp-base/RangeFor.hpp",
    ["2.range_for-3"]   = "dslings/exercises/other/cpp-base/RangeFor.hpp",
    ["3.array-0"]       = "dslings/exercises/array/Array.hpp",
    ["3.array-1"]       = "dslings/exercises/array/Array.hpp",
    ["3.array-2"]       = "dslings/exercises/array/Array.hpp",
    ["3.array-3"]       = "dslings/exercises/array/Array.hpp",
    ["3.array-4"]       = "dslings/exercises/array/Array.hpp",
    ["3.array-5"]       = "dslings/exercises/array/Array.hpp",
    ["3.array-6"]       = "dslings/exercises/array/Array.hpp",
    ["4.vector-0-0"]      = "dslings/exercises/array/Vector.hpp",
    ["4.vector-0-1"]      = "dslings/exercises/array/Vector.hpp",
    ["4.vector-0-all"]      = "dslings/exercises/array/Vector.hpp",
    ["4.vector-1-0"]      = "dslings/exercises/array/Vector.hpp",
    ["4.vector-1-1"]      = "dslings/exercises/array/Vector.hpp",
    ["4.vector-1-2"]      = "dslings/exercises/array/Vector.hpp",
    ["4.vector-1-all"]      = "dslings/exercises/array/Vector.hpp",
    ["4.vector-2"]      = "dslings/exercises/array/Vector.hpp",
    ["4.vector-3-0"]      = "dslings/exercises/array/Vector.hpp",
    ["4.vector-3-all"]      = "dslings/exercises/array/Vector.hpp",
    ["4.vector-4"]      = "dslings/exercises/array/Vector.hpp",
    ["4.vector-5"]      = "dslings/exercises/array/Vector.hpp",
    ["5.embedded-slist-0"]      = "dslings/exercises/linked-list/EmbeddedList.hpp",
    ["5.embedded-slist-1"]      = "dslings/exercises/linked-list/EmbeddedList.hpp",
    ["5.embedded-slist-2"]      = "dslings/exercises/linked-list/EmbeddedList.hpp",
    ["5.embedded-slist-3"]      = "dslings/exercises/linked-list/EmbeddedList.hpp",
    ["5.embedded-slist-4"]      = "dslings/exercises/linked-list/EmbeddedList.hpp",
    ["6.slinked-list-0"]      = "dslings/exercises/linked-list/SLinkedList.hpp",
    ["6.slinked-list-1"]      = "dslings/exercises/linked-list/SLinkedList.hpp",
    ["6.slinked-list-2"]      = "dslings/exercises/linked-list/SLinkedList.hpp",
    ["6.slinked-list-3"]      = "dslings/exercises/linked-list/SLinkedList.hpp",
    ["6.slinked-list-4"]      = "dslings/exercises/linked-list/SLinkedList.hpp",
    ["6.slinked-list-5"]      = "dslings/exercises/linked-list/SLinkedList.hpp",
    ["6.slinked-list-6"]      = "dslings/exercises/linked-list/SLinkedList.hpp",
    ["6.slinked-list-7"]      = "dslings/exercises/linked-list/SLinkedList.hpp",
    ["7.slinked-list-iterator-0"]      = "dslings/exercises/linked-list/SLinkedList.hpp",
    ["7.slinked-list-iterator-1"]      = "dslings/exercises/linked-list/SLinkedList.hpp",
    ["7.slinked-list-iterator-2"]      = "dslings/exercises/linked-list/SLinkedList.hpp",
    ["7.slinked-list-iterator-3"]      = "dslings/exercises/linked-list/SLinkedList.hpp",
    ["7.slinked-list-iterator-4"]      = "dslings/exercises/linked-list/SLinkedList.hpp",
    ["7.slinked-list-iterator-5"]      = "dslings/exercises/linked-list/SLinkedList.hpp",
}

function clear_screen()
    if os.host() == "windows" then
        os.exec("tools\\clear_screen.bat")
    else
        os.exec("clear")
    end
end

function print_info(target_name, built_targets, total_targets, current_file_path, output, status)

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
    if status then
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

    print("\nHomepage: https://github.com/Sunrisepeak/d2ds-courses")
end

-- main start
function main()
    local checker_pass = false
    local start_target = option.get("start_target")

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

    local skip = true
    for _, name in pairs(sorted_targets) do

        if skip and (name == start_target or string.find(name, start_target)) then
            skip = false;
        end

        if not skip then
            local files = targets[name]:sourcefiles()
            for  _, file in ipairs((files)) do
                local relative_path = path.relative(file, base_dir)
                local build_success = false
                local sleep_sec = 1000 * 0.1
                local output = ""

                local file_modify_time
                local compile_bypass_counter = 0

                while not build_success do
                    local curr_file_mtime = os.mtime(file)
                    if target_to_code_file[name] then
                        curr_file_mtime = curr_file_mtime + os.mtime(target_to_code_file[name])
                    end

                    if file_modify_time ~= curr_file_mtime then
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
                                end
                            }
                        }

                        if build_success then
                            try {
                                function () 
                                    output, _ = os.iorunv("xmake", {"r", name})
                                end,
                                catch
                                {
                                    function (e)
                                        output = e
                                        build_success = false
                                    end
                                }
                            }
                        end

                        local status = build_success

                        if type(output) == "string" then
                            if string.find(output, "❌") then
                                status = false
                                build_success = false
                            elseif string.find(output, "D2DS_WAIT") or string.find(output, "D2DS_RETURN") then
                                build_success = false
                            end
                        end

                        if build_success then
                            built_targets = built_targets + 1
                        else
                            sleep_sec = 1000 * 1
                        end

                        print_info(name, built_targets, total_targets, relative_path, output, status)
                        output = ""
                    else
                        compile_bypass_counter = compile_bypass_counter + 1
                    end

                    file_modify_time = curr_file_mtime
                    if compile_bypass_counter > 20 then
                        compile_bypass_counter = 0
                        file_modify_time = nil
                    end
                    os.sleep(sleep_sec)

                end
            end
        else
            built_targets = built_targets + 1
        end
    end

    local bingo = "\
        Bingo! 🎉🎉🎉\n \
You have completed all exercises\n \
Next: https://github.com/Sunrisepeak/dstruct\
"

    print_info("D2DS", total_targets, total_targets, "...", bingo, true)

end