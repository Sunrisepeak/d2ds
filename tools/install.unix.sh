#!/bin/bash

# ANSI color codes
RED='\033[31m'
GREEN='\033[32m'
YELLOW='\033[33m'
BLUE='\033[34m'
PURPLE='\033[35m'
CYAN='\033[36m'
RESET='\033[0m'

# check xmake status
echo -e "${PURPLE}[d2ds]: start detect environment and try to auto config...${RESET}"
if ! command -v xmake &> /dev/null
then
    echo -e "${PURPLE}[d2ds]: start install xmake...${RESET}"
    curl -fsSL https://xmake.io/shget.text | bash
else
    echo -e "${GREEN}[d2ds]: xmake installed${RESET}"
fi

if code --list-extensions | grep -q ms-vscode.cpptools
then
    echo -e "${GREEN}[d2ds]: vscode c++ extension installed${RESET}"
else
    echo -e "${PURPLE}[d2ds]: start install vscode c++ extension...${RESET}"
    code --install-extension ms-vscode.cpptools
fi

echo -e "${PURPLE}[d2ds]: auto config done.${RESET}"
echo -e ""
echo -e "${YELLOW}\tDive into Data Structures pre-v0.0.1 - open-sources${RESET}"
echo -e ""
echo -e "${CYAN} - main-repo: https://github.com/Sunrisepeak/d2ds${RESET}"
echo -e "${CYAN} - ebook: https://sunrisepeak.github.io/d2ds${RESET}"
echo -e "${CYAN} - courses: https://sunrisepeak.github.io/d2ds-courses${RESET}"
echo -e "${CYAN} - dstruct: https://github.com/Sunrisepeak/dstruct${RESET}"
echo -e "${CYAN} - issues: https://github.com/Sunrisepeak/d2ds/issues${RESET}"
echo -e ""
echo -e "[d2ds]: Try running ${RED}xmake dslings${RESET} to start your d2ds coding..."
echo -e "[d2ds]: run ${RED}xmake d2ds${RESET} get more info"