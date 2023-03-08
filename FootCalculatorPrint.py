
ComVal = {"On-Foot":0, "Motorbike": 372,"Car": 1115,"Bus": 131,"Carpol": 459,"Bicycle":0}
EatVal = {"Junk-Food":4818,"Home-Cooked-Meals": 629}
DietVal = {"Fruits/Vegetables":153,"Meat": 644,"Bread": 364}
LightVal = {"Yes":133,"No": 268}
AppVal = {"Yes":9,"No":18}
WaterVal = {"Yes":34,"No":274}
PaperVal = {"Yes":-105,"No":0}
GlassVal = {"Yes":-7,"No":0}
PlasticVal ={"Yes":-19,"No":0}
SteelVal = {"Yes":-86,"No":0}


def Footprint(Input):
    Rating = ComVal[Input[1]] + EatVal[Input[2]] + DietVal[Input[3]] + LightVal[Input[4]] + AppVal[Input[5]] + WaterVal[Input[6]] \
        + PaperVal[Input[7]] + GlassVal[Input[8]] + PlasticVal[Input[9]] + SteelVal[Input[10]]

    return Rating*1.55/1000
