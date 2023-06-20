from openpyxl import Workbook



def func(arg1, arg2):
    print("arg1, arg2: ", arg1, arg2)

 #def readFile():
    #with open("glad.h", 'r') as file:

print("hello python")
str1 = "1 2 3";
print("str1: ", str1)
str_list = str1.split(' ')
print("str_list: ", str_list)
func(1, 3)

# open file
file = open("glad.h", 'r')
wb = Workbook()
ws = wb.create_sheet("1")
lines = file.readlines()
print(lines[955])
for line in lines[956:]:
    if line.startswith("#define gl"):
        line_strs = line.split(" ")
        ws.append([line_strs[1]])
    

#ws.append(ls)
wb.save("excel.xlsx")
print("transfer success")
