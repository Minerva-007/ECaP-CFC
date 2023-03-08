from FootCalculatorPrint import Footprint

arg = []
with open("input.txt","r") as i:
    for x in i:
        arg.append(x.rstrip('\r\n'))

Response = Footprint(arg)

with open("output.txt","w") as o:
    o.write(arg[0])
    o.write('\n')
    o.write(str(Response))
    o.write('\n')
