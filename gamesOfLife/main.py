from random import randint
import os
import time

class GameOfLifeField:
    fullEmpty = True
    def __init__(self, percentageOfFill:int, width:int,heidth:int):
        self.percentageOfFill = percentageOfFill
        self.width = width
        self.heidth = heidth
    def generetion_filed(self):
        if self.percentageOfFill > 0:
            self.fullEmpty = False
        if self.percentageOfFill > 100 and self.percentageOfFill % 100 !=0:
            self.percentageOfFill %= 100
        elif self.percentageOfFill > 100 and self.percentageOfFill %100 == 0:
            self.percentageOfFill = 100
        numOfAllCells = self.width*self.heidth
        row =str()
        self.field = []
        numOfFillCells = int((numOfAllCells / 100) * self.percentageOfFill)
        for i in range(0,self.width+1):
            row+="_"
        self.field.append(row)
        row=""
        for i in range (1,self.heidth+1):
            row+="|"
            for j in range (1,self.width+1):
                 row+=" "
            row+="|"
            self.field.append(row)
            row = ""
        row=""
        for i in range(0,self.width+1):
            row+="-"
        self.field.append(row)
        row=""
        i =0
        while i < numOfFillCells:
            indexOfRow = randint(1,self.heidth-1)
            indexOfCol = randint(1,self.width-1)
            if self.field[indexOfRow][indexOfCol] == ' ':
                i+=1
                self.field[indexOfRow] = self.field[indexOfRow][:indexOfCol]+'#'+self.field[indexOfRow][indexOfCol+1:]
    def __str__(self):
        stringField = str()
        for i in self.field:
            stringField+=i
            stringField+="\n"
        return stringField
    def __repr__(self):
        return ("GameOfLifeField",self.width,self.heidth,self.percentageOfFill)
    def empty(self):
        if(self.fullEmpty == False):
            numOfEmpty = self.width*self.heidth - int(((self.width*self.heidth / 100) * self.percentageOfFill))
        else:
            numOfEmpty = self.width * self.heidth
        return numOfEmpty
    def fill(self):
        return int(((self.width*self.heidth / 100) * self.percentageOfFill))

def NumOfNeighbour(NewField:GameOfLifeField,i,j):
    neighbourCount =0
    if i > 0 and i < len(NewField.field)-1 and j > 0  and j < len(NewField.field[i])-2:
        if NewField.field[i][j+1] == '#':
            neighbourCount+=1
        if NewField.field[i+1][j] == '#':
             neighbourCount+=1
        if NewField.field[i+1][j+1] == '#':
           neighbourCount+=1
        if NewField.field[i][j-1] == '#':
             neighbourCount += 1
        if NewField.field[i-1][j] == '#':
             neighbourCount+=1
        if NewField.field[i-1][j-1] == '#':
            neighbourCount += 1
        if NewField.field[i-1][j+1] == '#':
            neighbourCount+= 1
        if NewField.field[i+1][j-1] == '#':
            neighbourCount += 1
    return neighbourCount

NewField = GameOfLifeField(10,50,50)
NewField.generetion_filed()
print(NewField)
while (True):
    for x in range(1, len(NewField.field)-1):
        for y in range(1,len(NewField.field[x])-1):
            neighbourCount = NumOfNeighbour(NewField, x, y)
            if NewField.field[x][y] == ' ':
                if neighbourCount >= 3:
                    NewField.field[x] =NewField.field[x][:y]+'#'+NewField.field[x][y+1:]
            else:
                if neighbourCount < 2 or neighbourCount > 3:
                    NewField.field[x] =NewField.field[x][:y]+' '+NewField.field[x][y+1:]
    print(NewField)
    time.sleep(1)
    os.system("cls")