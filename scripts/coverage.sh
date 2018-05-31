#! /usr/bin/env bash

echo 'Generating baseline coverage data file.'
lcov --capture --initial --directory . --output-file coverage_base.info

echo 'Generating coverage based on executed tests.'
lcov --capture --directory . --output-file coverage_test.info

echo 'Merging coverage tracefiles.'
lcov --add-tracefile coverage_base.info --add-tracefile coverage_test.info --output-file coverage_merge.info

echo 'Removing unwanted files from coverage.'
cov=`lcov --remove coverage_merge.info ./tests/* /usr/* -o coverage.info | tail -n 3 | head -n 1 | sed -e 's/  lines......: \([0-9]*\).*/\1/g'`

echo 'Calculated coverage rate is' $cov%
