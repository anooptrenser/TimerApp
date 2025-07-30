#!/bin/bash

REPORT="report.txt"

# Start report
echo "Sanity Check Report" > "$REPORT"
echo "Generated on: $(date)" >> "$REPORT"
echo "=================================" >> "$REPORT"

# Pull the latest code
echo -e "\n--- GIT PULL ---" >> "$REPORT"
git pull >> "$REPORT" 2>&1

# Clean and build the host release executable
echo -e "\n--- BUILD (make linux) ---" >> "$REPORT"
make clean >> "$REPORT" 2>&1
make linux >> "$REPORT" 2>&1

# Capture build warnings from make linux
echo -e "\n--- BUILD WARNINGS (make linux) ---" >> "$REPORT"
make clean > /dev/null 2>&1  
make linux 2>&1 | grep -i warning >> "$REPORT"

echo -e "\n--- STATIC ANALYSIS ---" >> "$REPORT"
if command -v cppcheck > /dev/null; then
    cppcheck --enable=all . appTimer simulateLED >> "$REPORT" 2>&1
else
    echo "cppcheck not found." >> "$REPORT"
fi

echo -e "\n--- MEMORY LEAK CHECK ---" >> "$REPORT"

if command -v valgrind > /dev/null && [ -x "release/appTimerexecutable" ]; then
    valgrind --leak-check=full release/appTimerexecutable >> "$REPORT" 2>&1
else
    echo "Valgrind or executable release/appTimerexecutable not found." >> "$REPORT"
fi

