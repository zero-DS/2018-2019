import pygame
import copy
import threading
import time
import timeit                     

from pygame.locals import *

screenWidth = 600  #게임판 가로
screenHeight = 480  #게임판 세로           

sHeight = screenHeight - 50

FPS=70                             #fps 70으로 조정
shownTime = 1500
speedRate = 1.5

WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GRAY = (166, 166, 166)            #색상들을 RGB코드를 이용해서 적은 튜

scoreStatus = [0, 0, 0]    #PERPECT GOOD MISS
boardList = ["PERFECT", "GOOD", "MISS", "COMBO", "SCORE"] 
effectOpacity = [0, 0, 0] #effect.png의 투명도 
score = 0  #score 변수값
combo = 0  #combo 변수값
showScore = 0


pygame.mixer.pre_init(44100, -16, 2, 2048)  #믹서 초기화 인수 설정 pre_init(frequency, size, channels, buffersize)  소리 옵
pygame.mixer.init()     #믹서 설정
pygame.init()
screen = pygame.display.set_mode((screenWidth, screenHeight), HWSURFACE | DOUBLEBUF)    #게임판 생성

pygame.display.set_caption('꿀잼 리듬게임')

clock = pygame.time.Clock()


backpic = pygame.image.load("backimg.png")  #배경 이미지
fallBar = pygame.image.load("fallbar.png")  #노트 이미지
fallBar = pygame.transform.scale(fallBar, (70, 5))  #막대 스케일 재설정
fallEffect = pygame.image.load("note-effect.png")  #노트 클릭시 이펙트 이미지
fallEffect = pygame.transform.scale(fallEffect, (70, 200))  #이펙트 이미지 스케일 재설정
allNoteList = pygame.sprite.Group()  #애니메이션

#노트 패턴 읽어오기
#note txt에 있는 값중 #1, #2, #3 뒤의 내용을 대입 받음
timeArr = []
showChaebo=[]
readTime = 0
weRockNote = open("note2.txt")  #note2의 내용 읽어오기
for line in weRockNote.readlines():
    if line[0] == '#':
        if (readTime > 0):
            showChaebo.append(timeArr)
            timeArr = []
        readTime = int(line[1])
        continue

    
    timeArr.append(int(float(line) * 1000))
weRockNote.close()
showChaebo.append(timeArr)
correctChaebo = copy.deepcopy(showChaebo)  #deepcopy 사용, 원본값이 변경되더라도 이전에 받은 값 유지

def getRuntime(): 
    end = timeit.default_timer()
    runtime = int((end - start) * 1000)
    return runtime


class Note(pygame.sprite.Sprite):
    def __init__(note, time):
        super().__init__()
        note.s_Time = time
        note.image = fallBar
        note.width = 50
        note.rect = note.image.get_rect()

    def update(note):
        if(note.rect.y > screenHeight):
            allNoteList.remove(note)
            return

        note.rect.y = screenHeight - ((note.s_Time - getRuntime()) / (shownTime / speedRate)) * sHeight - (screenHeight - sHeight)




#키가 눌러졌을 때만 TRUE 값으로 변경되면서 바로 FALSE값으로 돌아오면서 소리 출력
keyStatus=[False, False, False]

class keyReader(threading.Thread):
    def run(self):
        while playing:
            runtime = getRuntime()
            keys = pygame.key.get_pressed()
            
            if keys[pygame.K_a]:
                effectOpacity[0] = 255
                if(keyStatus[0] == False):
                    pygame.mixer.Sound("hihat.wav").play()
                    correctNote(runtime, 0)
                keyStatus[0] = True
            else:
                keyStatus[0] = False
            if keys[pygame.K_s]:
                effectOpacity[1] = 255
                if(keyStatus[1] == False):
                    pygame.mixer.Sound("hihat.wav").play()
                    correctNote(runtime, 1)
                keyStatus[1] = True
            else:
                keyStatus[1] = 0
            if keys[pygame.K_d]:
                effectOpacity[2] = 255
                if(keyStatus[2] == False):
                    pygame.mixer.Sound("hihat.wav").play()
                    correctNote(runtime, 2)
                keyStatus[2] = True
            else:
                keyStatus[2] = 0
            
            time.sleep(0.001)



#노트 점수 확인을 위한 함수
#abs를 이용하여 checkingChaebo에 저장된 시간과 키 입력 시간을 비교해 절댓값을 구하고 이를 바탕으로 점수 판정
def correctNote(time, key):
    global combo, score, scoreStatus

    absTime = 999999
    indexTime = 0
    if len(correctChaebo[key]) > 0:
            for i in range(0, len(correctChaebo[key])):
                if abs(correctChaebo[key][i] - time) < absTime:
                    absTime = abs(correctChaebo[key][i] - time)
                    indexTime = i
            if absTime < 80:
                if absTime < 40:   #범위가 40미만일 시 PERPECT 판정
                    scoreStatus[0] += 1
                    score = score + (combo * 0.01 + 1) * 300
                    combo += 1
                else:            #범위가 40이상 80미만일때 GOOD 판정
                    scoreStatus[1] += 1
                    score = score + (combo * 0.01 + 1) * 300
                    combo += 1
              
                correctChaebo[key].pop(indexTime)


        
class chaeboReader(threading.Thread):
    def run(self):
        while playing:
            for i in range(0, len(showChaebo)):
                if not len(showChaebo[i]) is 0:
                    end = timeit.default_timer()
                    runtime = int((end - start) * 1000)
                    temp = shownTime / speedRate
                    if showChaebo[i][0] - temp <= runtime:
                        makeNote(i, showChaebo[i][0])
                        showChaebo[i].pop(0)
            missChaebo()
            time.sleep(0.001)



#미스 확인을 위한 함수
def missChaebo():
    global combo, scoreStatus

    for i in range(0, len(correctChaebo)):
        if(len(correctChaebo[i]) > 0):
            if correctChaebo[i][0] - getRuntime() <= -80:
                correctChaebo[i].pop(0)
                scoreStatus[2] += 1
                combo = 0

def makeNote(line, time):
    note = Note(time)
    note.rect.x = 50 + fallBar.get_rect().width * line
    note.rect.y = 0
    allNoteList.add(note)
    
def blit_alpha(target, source, location, opacity):
    x = location[0]
    y = location[1]
    temp = pygame.Surface((source.get_width(), source.get_height())).convert()
    temp.blit(target, (-x, -y))
    temp.blit(source, (0, 0))
    temp.set_alpha(opacity)        
    target.blit(temp, location)
                


def printGame():
    try:
        global showScore, scoreStatus, backpic
        
        screen.fill((0, 0, 0))
        backpic = pygame.image.load("backimg.png")
        backpic = pygame.transform.scale(backpic, (screenWidth, screenHeight))
        screen.blit(backpic, backpic.get_rect())

        allNoteList.update()
        allNoteList.draw(screen)

        pygame.draw.line(screen, WHITE, [50 + fallBar.get_rect().width * 0, 0], [50 + fallBar.get_rect().width * 0, screenHeight], 2)
        for i in range(1, 3):
            pygame.draw.line(screen, WHITE, [50 + fallBar.get_rect().width * i, 0], [50 + fallBar.get_rect().width * i,screenHeight], 2)
        pygame.draw.line(screen, WHITE, [50 + fallBar.get_rect().width * 3, 0], [50 + fallBar.get_rect().width * 3,screenHeight], 2)
            
        pygame.draw.line(screen, WHITE, [50, sHeight], [50 + fallBar.get_rect().width * 3, sHeight], 2)
        for i in range(0, 3):
            gameFont = pygame.font.Font("dabang.ttf", 36)
            keyRect = pygame.Rect(50 + fallBar.get_rect().width * i + 2, sHeight + 2, fallBar.get_rect().width - 2, screenHeight - sHeight - 2)
            if i == 0:
                pygame.draw.rect(screen, GRAY, keyRect)
                playkey = gameFont.render('A', 1, WHITE)
                screen.blit(playkey, keyRect)
            elif i == 1:
                pygame.draw.rect(screen, GRAY, keyRect)
                playkey = gameFont.render('S', 1, WHITE)
                screen.blit(playkey, keyRect)
            else:
                pygame.draw.rect(screen, GRAY, keyRect)
                playkey = gameFont.render('D', 1, WHITE)
                screen.blit(playkey, keyRect)

        for i in range(0, len(effectOpacity)):
            if effectOpacity[i] != 1:
                if effectOpacity[i] >= 30:
                    effectOpacity[i] -= 30
                    blit_alpha(screen, fallEffect, (50 + fallEffect.get_rect().width * i, 155 + 75), effectOpacity[i])
                else:
                    effectOpacity[i] = 0
                    blit_alpha(screen, fallEffect, (50 + fallEffect.get_rect().width * i, 155 + 75), effectOpacity[i])

        gameFont = pygame.font.Font("dabang.ttf", 20)
 
        if showScore < int(score):
            showScore += 20
            
        for i in range(0, 3):
            label = gameFont.render(boardList[i] , 1, WHITE)
            screen.blit(label, (350, 100 +  i * 50))
            label = gameFont.render(str(scoreStatus[i]) , 1, WHITE)
            screen.blit(label, (500, 100 + i * 50))

        label = gameFont.render(boardList[3], 1, WHITE)
        screen.blit(label, (350, 250))
        label = gameFont.render(str(combo), 1, WHITE)
        screen.blit(label, (500, 250))
        label = gameFont.render(boardList[4], 1, WHITE)
        screen.blit(label, (350, 300))
        label = gameFont.render(str(int(showScore)), 1, WHITE)
        screen.blit(label, (500, 300))

        pygame.display.flip()

    except:
        pass

playing = True
pygame.mixer.Sound("bgm1.wav").play()
clock = pygame.time.Clock()
start = timeit.default_timer()
keyReader().start()
chaeboReader().start()

while playing:

    clock.tick(FPS)

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            playing = False
            pygame.quit()
            break
            exit()   
    printGame()
    

