import cv2 as cv
import numpy as np
import imutils
img = cv.imread('img/5.jpg')
#腐蚀操作
kernel = cv.getStructuringElement(cv.MORPH_RECT,(5,5)) #ksize=5,5
dst=cv.erode(img,kernel)
# 转换颜色空间 BGR 到 HSV
hsv = cv.cvtColor(dst, cv.COLOR_BGR2HSV)
#HSV颜色储存在 7*2*3 的三维数组
HSV_mat = np.array([[[81,105,72],[112,255,255]],	#HSV中蓝色的范围小三角形[lower_HSV,upper_HSV]
					[[145,104,123],[180,255,255]],	# 红色四边形角形
					[[15,144,107],[75,255,255]],	# 橙色小三角形
					[[34,56,58],[73,255,255]],		# 绿色大三角形
					[[103,26,109],[166,255,255]],	# 紫色正方形
					[[27,77,87],[30,255,255]],		# 黄色小三角
					[[0,63,222],[180,90,255]]]		# 粉色小三角
					)
#循环识别7种颜色
for i in range(np.shape(HSV_mat)[0]):#np.shape(HSV_mat)[0]输出x维度大小
	mask = cv.inRange(hsv, HSV_mat[i][0][:], HSV_mat[i][1][:])
	# 将掩膜和图像逐像素相加
	res = cv.bitwise_and(img,img, mask= mask)
	#寻找形状
	cnts = cv.findContours(mask, cv.RETR_EXTERNAL,
		cv.CHAIN_APPROX_SIMPLE)
	cnts = imutils.grab_contours(cnts)
	# loop over the contours
	for c in cnts:
		# 计算形状中心点
		M = cv.moments(c)
		if M["m00"]>=2000:#只寻找面积大于2000的形状
			#一阶矩与零阶矩相除得到中心点x，y（单位为像素）
			cX = int(M["m10"] / M["m00"])
			cY = int(M["m01"] / M["m00"])
			# 画出形状和中心点
			cv.drawContours(img, [c], -1, (0, 255, 0), 9)
			cv.circle(img, (cX, cY), 15, (0, 0, 255), -1)
			print("cx:"+str(cX)+","+"cy:"+str(cY))
			cv.putText(img, "center", (cX - 20, cY - 20),cv.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2)
	print("--------%d---------\n"%(i+1))#标号


cv.namedWindow('img',cv.WINDOW_NORMAL)
cv.imshow("img", img)
cv.waitKey(0)
cv.destroyAllWindows()
