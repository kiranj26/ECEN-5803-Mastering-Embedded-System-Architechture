
"""
/********************************************************************
* @file get_kernel_details.py
* System Information Retrieval Script for Linux - Project 3 Module 3
*
* This script automatically retrieves various system information
* details and saves them to individual files for later analysis.
*
* @author Kiran Jojare, Viraj Patel
* @see <a href="https://www.gnu.org/software/bash/manual/">Bash Reference Manual</a>
* @see <a href="https://docs.python.org/3/library/os.html">Python OS Library Documentation</a>
********************************************************************/
"""

import os
import platform
import time

# Directory where output files will be saved
output_directory = "/home/pi/Desktop/OS_Info"

def execute_command(command, output_file):
    """
    Executes a system command and redirects the output to a specified file.
    
    Args:
    command (str): The system command to be executed.
    output_file (str): The name of the file where the command output will be saved.
    """
    full_command = f'{command} > {output_directory}/{output_file}'
    os.system(full_command)

def show_menu():
    """
    Displays the menu options for system information retrieval.
    The menu is displayed for informational purposes.
    """
    menu_options = {
        "1": "List all Running Process",
        "2": "Get Kernel Name",
        "3": "Get Kernel Version",
        "4": "Get Kernel Dump",
        "5": "Real time Linux Monitoring",
        "6": "Real time Disk Utilization",
        "7": "Real time Memory Consumption",
        "8": "Show all active processes",
        "9": "Show all background processes",
        "10": "Number of processes per user",
        "11": "Get device IP",
        "12": "Get Physical Memory Stats",
        "13": "Get Swap Memory Stats",
        "14": "Show RAM Stats"
    }

    print("-----------------------------------------------------------")
    for key, value in menu_options.items():
        print(f"{key}. {value}")
    print("-----------------------------------------------------------")

def main():
    """
    Main function to execute system information commands and save their outputs.
    Each command's output is saved to a distinct text file.
    """
    show_menu()

    # Execute commands and save outputs to files
    execute_command('ps aux', '1_running_processes.txt')
    execute_command('uname --kernel-name', '2_kernel_name.txt')
    execute_command('uname --kernel-version', '3_kernel_version.txt')
    execute_command('dmesg', '4_kernel_dump.txt')
    execute_command('timeout 2 atop', '5_real_time_linux_monitoring.txt')
    execute_command('timeout 2 atop -d', '6_disk_utilization.txt')
    execute_command('timeout 2 atop -m', '7_memory_consumption.txt')
    execute_command('timeout 2 atop -a', '8_active_processes.txt')
    execute_command('timeout 2 atop -c', '9_background_processes.txt')
    execute_command('timeout 2 atop -au', '10_processes_per_user.txt')
    execute_command("ifconfig | grep 'broadcast' | awk '{print $2}'", '11_device_ip.txt')
    execute_command("free -m | grep 'Mem' | awk '{print  \"Physical Memory Stats in MB: \", \"Total:\", $2,  \"Used:\", $3,\"Free:\", $4, \"Shared:\", $5,\"Buff/Cache:\", $6, \"Available:\", $7}'", '12_physical_memory_stats.txt')
    execute_command("free -m | grep 'Swap' | awk '{print  \"Swap Memory Stats in MB: \", \"Total:\", $2,  \"Used:\", $3,\"Free:\", $4, \"Shared:\", $5,\"Buff/Cache:\", $6, \"Available:\", $7}'", '13_swap_memory_stats.txt')
    execute_command('lscpu', '14_ram_stats.txt')

if __name__ == "__main__":
    main()

