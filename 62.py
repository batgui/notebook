
import sys

string = ""
stringarray = list()

def DFS(string):
    if (len(string) == 0):
        return True
    for i in range(1, len(string) + 1):
        if(string[0:i] in stringarray):
            if(DFS(string[i:len(string) + 1])):
                return True
            
    return False

string = sys.stdin.readline().strip()


line = sys.stdin.readline().strip()
#line = "thisis dog"
stringarray = line.split()
#string = "thidsisdog"
result = DFS(string)
print(result)


