#!/bin/bash

# ANSI color code for purple
PURPLE='\033[0;35m'
NC='\033[0m' # No Color

# set color
echo ""	
printf "$3"

# Function to print the top, middle, or bottom border
print_border_top() {
    local length=$1
    echo -n "╔"
    for ((i=0; i<=length; i++)); do
        echo -n "═"
    done
    echo "╗"
}

# Function to print the top, middle, or bottom border
print_border_bottom() {
    local length=$1
    echo -n "╚"
    for ((i=0; i<=length	; i++)); do
        echo -n "═"
    done
    echo "╝"
}

# Function to print the middle part with text
print_middle() {
    local text1=$1
    local text2=$2
    local total_length=$(( ${#text1} + ${#text2} + 5 ))
    echo -n "║  $text1"
    for ((i=0; i<total_length - ${#text1} - ${#text2} - 5; i++)); do
        echo -n " "
    done
    echo ":    $text2   ║"
}

# Main script starts here
param1="$1"
param2="$2"

# Calculate the total length
total_length=$(( ${#param1} + ${#param2} + 9 )) # 9 for additional characters and spaces

# Print the box
print_border_top $total_length
print_middle "$param1" "$param2"
print_border_bottom $total_length

# reset color
printf "\033[0m"