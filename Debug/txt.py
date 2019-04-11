import sys
result=[]
with open('a.txt','r') as f:
	for line in f:
		result.append(line.strip('\n').split(',')[0])
print(result)
print result[0].split()
for i in range(len(result)):
	print result[i].split()
