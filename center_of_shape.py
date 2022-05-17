# # import the necessary packages
# import argparse
# import imutils
# import cv2
# # construct the argument parse and parse the arguments
# ap = argparse.ArgumentParser()
# ap.add_argument("-i", "--image", required=True,
# 	help="path to the input image")
# args = vars(ap.parse_args())
# # load the image, convert it to grayscale, blur it slightly,
# # and threshold it
# image = cv2.imread(args["image"])
# gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
# blurred = cv2.GaussianBlur(gray, (5, 5), 0)
# thresh = cv2.threshold(blurred, 60, 255, cv2.THRESH_BINARY)[1]
# # find contours in the thresholded image
# cnts = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL,
# 	cv2.CHAIN_APPROX_SIMPLE)
# cnts = imutils.grab_contours(cnts)
# # loop over the contours
# for c in cnts:
# 	# compute the center of the contour
# 	M = cv2.moments(c)
# 	cX = int(M["m10"] / M["m00"])
# 	cY = int(M["m01"] / M["m00"])
# 	# draw the contour and center of the shape on the image
# 	cv2.drawContours(image, [c], -1, (0, 255, 0), 2)
# 	cv2.circle(image, (cX, cY), 7, (255, 255, 255), -1)
# 	cv2.putText(image, "center", (cX - 20, cY - 20),
# 		cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2)
# 	# show the image
# 	cv2.imshow("Image", image)
# 	cv2.waitKey(0)

# import numpy as np
# import cv2 as cv
#图片加载与显示
# img = cv.imread('1.jpeg',1)
# cv.namedWindow('image',cv.WINDOW_AUTOSIZE)
# cv.imshow('image',img)
# cv.waitKey(0)
# cv.destroyAllWindows()

#画图
# 创建黑色的图像
# img = np.zeros((512,512,3), np.uint8)
# # 绘制一条厚度为5的蓝色对角线
# cv.line(img,(0,0),(511,511),(255,0,0),1)
# cv.rectangle(img,(384,0),(510,128),(0,255,0),3)
# cv.circle(img,(447,63), 63, (0,0,255), -1)
# cv.ellipse(img,(256,256),(100,50),0,0,360,(0,255,255),-1)
# pts = np.array([[10,5],[20,30],[70,20],[50,10]], np.int32)
# pts = pts.reshape((-1,1,2))
# cv.polylines(img,[pts],True,(0,255,255))
# font = cv.FONT_HERSHEY_SIMPLEX #字体类型
# cv.putText(img,'OpenCV',(10,300), font, 4,(255,255,255),10,cv.LINE_AA)
# #参数是OpenCV 输入文本数据，放置文本的位置坐标，字体类型，字体大小，颜色为白色，厚度为2，线条类型
# cv.namedWindow('image',cv.WINDOW_AUTOSIZE)
# cv.imshow('image',img)
# cv.waitKey(0)
# cv.destroyAllWindows()

# img = cv.imread('1.jpeg')
# ball = img[280:340, 330:390]
# img[273:333, 100:160] = ball
# cv.namedWindow('image',cv.WINDOW_AUTOSIZE)
# cv.imshow('image',img)
# cv.waitKey(0)
# cv.destroyAllWindows()


import cv2 as cv
import numpy as np
import imutils
img = cv.imread('img/5.jpg')
kernel = cv.getStructuringElement(cv.MORPH_RECT,(1,1)) #ksize=5,5
dst=cv.erode(img,kernel)
# cv.namedWindow('erode',cv.WINDOW_NORMAL)
# cv.imshow("erode", dst)
# 转换颜色空间 BGR 到 HSV
hsv = cv.cvtColor(dst, cv.COLOR_BGR2HSV)
# # 定义HSV中蓝色的范围小三角形
# lower_HSV = np.array([81,105,72])
# upper_HSV = np.array([112,255,255])
# # 红色四边形角形
# lower_HSV = np.array([145,104,123])
# upper_HSV = np.array([180,255,255])
# # 橙色小三角形
# lower_HSV = np.array([15,144,107])
# upper_HSV = np.array([75,255,255])
# # 绿色大三角形
# lower_HSV = np.array([34,56,58])
# upper_HSV = np.array([73,255,255])
# # 紫色正方形
# lower_HSV = np.array([103,26,109])
# upper_HSV = np.array([166,255,255])
# 黄色正方形
lower_HSV = np.array([27,77,87])
upper_HSV = np.array([30,255,255])
# # 粉色小三角
# lower_HSV = np.array([0,63,222])
# upper_HSV = np.array([180,90,255])

# 设置HSV的阈值使得只取蓝色
mask = cv.inRange(hsv, lower_HSV, upper_HSV)
# 将掩膜和图像逐像素相加
res = cv.bitwise_and(img,img, mask= mask)
cv.namedWindow('mask',cv.WINDOW_NORMAL)
# cv.namedWindow('res',cv.WINDOW_NORMAL)
cv.imshow('mask',mask)
# cv.imshow('res',res)


cnts = cv.findContours(mask, cv.RETR_EXTERNAL,
	cv.CHAIN_APPROX_SIMPLE)
cnts = imutils.grab_contours(cnts)

# #findContours测试
# cv.drawContours(res,cnts,-1,(0,0,255),3)
# cv.namedWindow('findContours',cv.WINDOW_NORMAL)
# cv.imshow('findContours',res)


# loop over the contours
for c in cnts:
	# compute the center of the contour
	M = cv.moments(c)
	if M["m00"]>=2000:#面积大于2000
		cX = int(M["m10"] / M["m00"])
		cY = int(M["m01"] / M["m00"])
		# draw the contour and center of the shape on the image
		cv.drawContours(img, [c], -1, (0, 255, 0), 9)
		cv.circle(img, (cX, cY), 15, (0, 0, 255), -1)
		print("cx:"+str(cX)+","+"cy:"+str(cY))
		cv.putText(img, "center", (cX - 20, cY - 20),cv.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2)


cv.namedWindow('img',cv.WINDOW_NORMAL)
cv.imshow("img", img)
cv.waitKey(0)
cv.destroyAllWindows()
 