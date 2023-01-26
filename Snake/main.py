import pygame
from random import randint
import sys
FPS = 60
widthScreen = 800  # ширина экрана
heidthScreen = 600  # высота экрана
numOfAppleInField = 3

WHITE = (255, 255, 255)
BLUE = (0, 70, 225)
GREEN = (0, 255, 0)
RIGHT = "RIGHT"
LEFT = "LEFT"
UP = "UP"
DOWN = "DOWN"
STOP = "stop"
SPEED = 3
sc = pygame.display.set_mode((widthScreen, heidthScreen))
clock = pygame.time.Clock()
appleSize =20
headSnakeSize =30

class Apple:
    def __init__(self, x,y):
        self.x = x
        self.y = y
        self.exist = True
        self.color = (255, 0, 0)
    def drawApple(self,sc):
        pygame.draw.rect(sc, self.color, (self.x, self.y ,appleSize,appleSize))



class Snake:
    def __init__(self):
        self.score = 0
        self.color = GREEN
        self.direction = UP
        self.change_to = self.direction
        x = widthScreen / 2
        y = widthScreen / 2
        self.elements = [[x,y],[x, y + 60]]
        self.snake_head_pos = self.elements[0]

    def change_head_position(self):
        if self.direction == "RIGHT":
            self.snake_head_pos[0] += 3
        elif self.direction == "LEFT":
            self.snake_head_pos[0] -= 3
        elif self.direction == "UP":
            self.snake_head_pos[1] -= 3
        elif self.direction == "DOWN":
            self.snake_head_pos[1] += 3

    def BodyMeshanism(self, apple:Apple):
        self.elements.insert(0, list(self.snake_head_pos))
        rect1 = pygame.Rect((self.snake_head_pos[0],self.snake_head_pos[1],appleSize,appleSize))
        rect2 = pygame.Rect((apple.x,apple.y,appleSize,appleSize))
        if(pygame.Rect.colliderect(rect1,rect2)):
            apple.x, apple.y = randint(1, int(widthScreen / 10))*10, randint(1, int(heidthScreen/10))*10
            self.score += 1
        else:
            self.elements.pop()
    def draw (self, sc):
        sc.fill(WHITE)
        for i in self.elements:
            pygame.draw.rect(sc, GREEN, (i[0], i[1],headSnakeSize, headSnakeSize))

    def check_for_boundaries(self):
        if any((self.snake_head_pos[0] > widthScreen-30 or self.snake_head_pos[0] < 0,
                self.snake_head_pos[1] > heidthScreen-10 or self.snake_head_pos[1] < 0)):
            sys.exit()




snake = Snake()
motion = STOP
apples = []
speedY = SPEED
speedX = SPEED
for i in range(1, numOfAppleInField+1):
    newApple = Apple(randint(20, widthScreen), randint(20, heidthScreen))
    apples.append(newApple)
while 1:
    for i in pygame.event.get():
        if i.type == pygame.QUIT:
            sys.exit()
        elif i.type == pygame.KEYDOWN:
            if i.key == pygame.K_LEFT:
                motion = LEFT
            elif i.key == pygame.K_RIGHT:
                motion = RIGHT
            elif i.key == pygame.K_UP:
                motion = UP
            elif i.key == pygame.K_DOWN:
                motion = DOWN
    if motion == LEFT and snake.direction != RIGHT:
        speedX = -SPEED
        speedY = 0
        snake.direction = LEFT
    elif motion == RIGHT and snake.direction != LEFT:
        speedX = SPEED
        speedY = 0
        snake.direction = RIGHT
    elif (motion == UP or motion == STOP) and snake.direction != DOWN:
        speedY = -SPEED
        speedX = 0
        snake.direction = UP
    elif motion == DOWN and snake.direction != UP:
        speedY = SPEED
        speedX = 0
        snake.direction = DOWN
    snake.change_head_position()
    for i in apples:
        snake.BodyMeshanism(i)
    snake.draw(sc)
    for i in apples:
        if i.exist == True:
            i.drawApple(sc)
        else:
            i.newPosition(randint(10, widthScreen), randint(10, heidthScreen))
            i.exist = True
    snake.check_for_boundaries()
    pygame.display.update()
    clock.tick(FPS)
