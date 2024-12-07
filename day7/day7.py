def readAndFormatData(filename):
    data= open(filename, 'r').read().split('\n')
    data=[line.split(' ') for line in data]
    return data

def part1(data):
    result = 0
    for line in data:
    	answer = int(line[0][:-1])
    	values = [int(val) for val in line[1:]]
    	n_operators = len(values)-1
    	n_possibilities = 2**n_operators
    	num = 0
    	while num < n_possibilities:
    		binary = format(num, f'0{n_operators}b')
    		test = values[0]
    		for i in range(n_operators):
    			if binary[i]=='1':
    				test += values[i+1]
    			else:
    				test *= values[i+1]
    		if test==answer:
    			result+=answer
    			break
    		num+=1
    return result
    
def to_ternary (n):
    if n == 0:
        return '0'
    nums = []
    while n:
        n, r = divmod(n, 3)
        nums.append(str(r))
    return ''.join(reversed(nums))
 
def part2(data):
    result = 0
    tot = len(data)
    for line in data:
    	answer = int(line[0][:-1])
    	values = [int(val) for val in line[1:]]
    	n_operators = len(values)-1
    	n_possibilities = 3**n_operators
    	num = 0
    	while num < n_possibilities:
    		ternary = to_ternary(num)
    		while len(ternary)<n_operators:
    			ternary = '0'+ternary
    		test = values[0]
    		for i in range(n_operators):
    			if ternary[i]=='0':
    				test += values[i+1]
    			elif ternary[i]=='1':
    				test *= values[i+1]
    			else:
    				test = int(str(test)+str(values[i+1]))
    		if test==answer:
    			result+=answer
    			break
    		num+=1
    return result

if __name__ == "__main__":
    data=readAndFormatData('input.txt')
    print(f'Part 1) {part1(data)}')
    print(f'Part 2) {part2(data)}')