#!/bin/bash
# filepath: /workspaces/CppCodingDojo/scripts/run_tests.sh

# Run Catch2 tests and log the output
./build/Tests --reporter compact | tee test_results.log

# Count occurrences of 'failed:' in test_results.log
failed_count=$(grep -c 'failed:' test_results.log)

# Set the result variable based on the count
if [[ $failed_count -gt 0 ]]; then
    commit_msg="${failed_count} failed tests"
else
    commit_msg="ok"
fi

# Remove temporary log file
rm test_results.log

# Commit all current changes with the commit message
git add .
git commit -m "$commit_msg"