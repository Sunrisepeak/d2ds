import("core.base.option")

local d2ds_repo = "https://github.com/Sunrisepeak/d2ds"

function d2ds_useage()
    print("Useage\n")
    --d2ds
    print("$ xmake d2ds [update | info | help]")
    print("\ncommand list:")
    print("\tupdate\t sync/update d2ds's repository code")
    print("\tinfo\t version info")
    print("\thelp\t useage...")
    --dsligs
    print("")
    print("$ xmake dslings [command] [target_name]")
    print("\ncommand list:")
    print("\t-s, target_name\t execute from target_name(support fuzzy match)")
end

function d2ds_info()
    print("d2ds version: pre-v0.0.1")
    print("dslings version: pre-v0.0.1")
    print(string.format("repo: %s", d2ds_repo))
end

function sync_repo()
    cmd = string.format("git pull %s main --rebase", d2ds_repo)
    print("start sync mian-repo...")
    os.exec(cmd)
    print("start update submodule...")
    os.exec("git submodule update")
end

function main()
    local command = option.get("command")
    if command == "update" then
        sync_repo()
    elseif command == "help" then
        d2ds_useage();
    elseif command == "info" then
        d2ds_info();
    else
        d2ds_info();
        print("--------------------------------------")
        d2ds_useage();
    end
end