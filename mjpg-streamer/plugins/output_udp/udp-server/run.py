#! /usr/bin/python2

import sys
import cv
import Image
import PIL
import numpy
import pygame
import time

WIDTH = 640
HEIGHT = 320
camera = cv.CreateCameraCapture(0)

corners = []

def get_image():    
    global corners 
    corners = []
    im = cv.QueryFrame(camera)
    im_rgb = cv.GetMat(im)
    cv.CvtColor(im,im_rgb,cv.CV_BGR2RGB) #getting the rgbimage

#worst image grayscaling of all time.
    #image = cv.CreateImage(cv.GetSize(im),cv.IPL_DEPTH_32F,3)
    #cv.ConvertScale(im,image)
    #new_image = cv.CreateImage(cv.GetSize(im),cv.IPL_DEPTH_32F,1)
    #cv.CvtColor(image,new_image,cv.CV_BGR2GRAY)
    #gray_image = cv.CreateImage(cv.GetSize(im),cv.IPL_DEPTH_8U,1)
    #cv.ConvertScale(new_image,gray_image)
    yuv = cv.CreateImage(cv.GetSize(im),8,3)
    gray_image = cv.CreateImage(cv.GetSize(im),8,1)
    cv.CvtColor(im,yuv,cv.CV_BGR2YCrCb)
    cv.Split(yuv,gray_image,None,None,None)

    eig_image = cv.CreateImage(cv.GetSize(gray_image),cv.IPL_DEPTH_32F,1)
    temp_image = cv.CreateImage(cv.GetSize(gray_image),cv.IPL_DEPTH_32F,1)
    
    
    for (x,y) in cv.GoodFeaturesToTrack(gray_image,eig_image,temp_image, 300, 0.01, 1.0, useHarris = True):
        corners.append([WIDTH-x,y])
    
    return pygame.transform.flip(pygame.image.frombuffer(im_rgb.tostring(),cv.GetSize(im_rgb),"RGB"),True,False)
    
#old_difs = [[0]*(HEIGHT/10) for x in xrange(WIDTH/10)]
#new_difs = [[0]*(HEIGHT/10) for x in xrange(WIDTH/10)]


def find_difs(image_old, image_new, surface):
    if image_old and image_new:
        #for x in range(WIDTH/10):
        #    for y in range(HEIGHT/10):
        #        old_difs[x][y] = new_difs[x][y]
        x,y = 0,0
        sensitivity = 175
        while x < WIDTH:
            y = 0
            while y < HEIGHT:
                #print image_old.get_at((x,y))
                color1 = image_old.get_at((x,y))
                color2 = image_new.get_at((x,y))
                total_dif = abs(color1.r-color2.r) + abs(color1.g-color2.g) + abs(color1.b-color2.b)
                if total_dif > sensitivity:
                    pygame.draw.rect(surface,pygame.color.Color("red"),(x,y,3,3),3)                
                #new_difs[x/10][y/10] = total_dif-sensitivity
                #if abs(new_difs[x/10][y/10]-old_difs[x/10][y/10]) > sensitivity*1.5:
                #    pygame.draw.rect(surface,pygame.color.Color("green"),(x,y,3,3),4)                
                y+=10
            x+=10
        for i in range(len(corners)):
            if corners[i][0] != 0 or corners[i][1] != 0: 
                pygame.draw.rect(surface,pygame.color.Color("green"),(corners[i][0],corners[i][1],3,3),4)
            
pygame.init()
window = pygame.display.set_mode((WIDTH,HEIGHT))
screen = pygame.display.get_surface()
print("Made window")

oldimage, currentimage = None, None
while True:
    events = pygame.event.get()
    for event in events:
        if event.type == pygame.QUIT or event.type == pygame.KEYDOWN:
            sys.exit(0)
    oldimage = currentimage
    currentimage = get_image()
    if currentimage:
        screen.blit(currentimage,(0,0))
    find_difs(oldimage,currentimage,screen)
    
    pygame.display.flip()
    #time.sleep(.1)


