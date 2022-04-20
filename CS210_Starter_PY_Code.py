import re
import string

def read_File(): # creates function to read from input file
    
    input_file = open("CS210_Project_Three_Input_File.txt") # opens text file
    items = input_file.read().split() # reads and stores file text
    
    single_item = sorted(set(items))

    for i in single_item: # prints frequency of item
        
        print(i, ":",  items.count(i))
        print()

    input_file.close() # closes input_file

def find_Frequency(v): # creates function to find frequency of item in input file

    input_file = open("CS210_Project_Three_Input_File.txt")
    items = input_file.read().split()
    single_item = sorted(set(items))
    input_file.close() 

    total = 0 # initializes item count
    total_inventory = 0  # counts iterations
    total_inventory_count = 0 # total inventory stored in file

    for i in single_item: # gets number of items in file
        total_inventory_count += 1

    for i in single_item: # gets frequency of item from user input
        temp_string = i
        total_inventory += 1
        if (temp_string == v):
            total = items.count(i)
            total_inventory -= 1 # this determines that the item was accessed at least once during iteration --  used to determine if user input actually in file
        if (temp_string != v and total_inventory == total_inventory_count):
            return -1 # item not found in file
    
    return total


def read_And_Write_File(): # reads input file, creates and writes to frequency.dat file, generates histogram

    input_file = open("CS210_Project_Three_Input_File.txt")
    data = open("frequency.dat", "w")
    items = input_file.read().split()
    single_item = sorted(set(items))
   
    for i in single_item: # write to frequency.dat file
        data.write(i)
        data.write(" ")
        data.write(str(items.count(i)))
        data.write("\n")
    
    data.close()

    histogram_data = open("frequency.dat", "r") # read-only from frequency file
    product_data = histogram_data.readlines()

    temp_freq = 0
    temp_product = ""

    for line in product_data:
        temp_int = 0
        temp_string = line.split() # splits item name and frequency
        for word in temp_string:
            temp_int += 1
            if (temp_int == 1):
                temp_product = word
                print(temp_product, end = " ")
            if (temp_int == 2):
                temp_freq = int(word) 
        
        for i in range(temp_freq): # generates histogram
            print("*", end = "")
        print("\n")