import os

while True:
    numSim = int(input("Enter number of simulations: "))
    if numSim < 1:
        print("Value must be more than 0")
    break

while True:
    aiStrength = int(input("Enter AI strength: "))
    if aiStrength < 1 or aiStrength > 20000:
        print("Value must be between 1 and 20,000")
    break

for i in range(numSim):
    arg = "./2048-AI " + str(aiStrength)
    os.system(arg)
    

