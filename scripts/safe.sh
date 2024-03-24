#!/bin/bash

safe() {
	$@
	if [ $? -ne 0 ]; then
		echo "Build error"
		exit 1
	fi
}
