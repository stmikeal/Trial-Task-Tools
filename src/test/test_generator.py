from random import randint, choice
import sys

randX = lambda: randint(-2147483648, 2147483647) 
randLen = lambda: randint(1, 200) 

def gen_request(number, length):
	request = [choice(["n", "m"]) for _ in range(number)]
	return list(map(lambda x: (x, randX() if x == "n" else randint(1, length)), request))
	
def get_answer(req, collection):
	if req[0] == "m":
		return str(collection[req[1] - 1])
	return str(len(filter(lambda x: x < req[1], collection)))

def gen_single_test(path, number):
	test = open(path + "/" + str(number) + ".test", 'w')
	answer = open(path + "/" + str(number) + ".answer", 'w')
	collection = [randX() for _ in range(randLen())]
	collection_str = list(map(lambda x: "k " + str(x) + " ", collection))
	requests = gen_request(randLen(), len(collection))
	requests_str = list(map(lambda x: x[0] + " " + str(x[1]) + " ", requests))
	test.write("".join(collection_str + requests_str) + '\n')
	collection.sort()
	answer.write(" ".join([get_answer(req, collection) for req in requests]))
	test.close()
	answer.close()

def main(args):
	amount = int(args[0])
	path = args[1]
	for i in range(amount):
		gen_single_test(path, i)

if __name__ == "__main__":
	main(sys.argv[1:])
