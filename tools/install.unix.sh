#!/bin/bash

# check xmake status
if ! command -v xmake &> /dev/null
then
    curl -fsSL https://xmake.io/shget.text | bash
else
    echo "xmake installed"
fi