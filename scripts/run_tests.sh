#!/bin/bash
# filepath: /workspaces/CppCodingDojo/scripts/run_tests.sh

# Run Catch2 tests and log the output
./Debug/Tests --reporter compact | tee test_results.log

# Count the number of failed tests and append the result with the latest Git commit hash and timestamp
grep -c 'failed' test_results.log | xargs -I {} echo "$(git rev-parse --short HEAD): {} at $(date +'%Y-%m-%d %H:%M:%S')" >> failed_tests_count.log

# Remove temporary log file
rm test_results.log