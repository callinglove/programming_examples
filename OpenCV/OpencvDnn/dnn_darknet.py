from PIL import Image
import numpy as np
import cv2


yoloCfg = r"F:\github\chineseocr\models\text.cfg"
yoloWeights = r"F:\github\chineseocr\models\text.weights"
path = r"C:\Users\golden\Desktop\黑圈\13.129.17.81.jpg"
textNet  = cv2.dnn.readNetFromDarknet(yoloCfg,yoloWeights)

im = Image.open(path).convert("RGB")
img = np.array(im)

thresh=0
h,w = img.shape[:2]

inputBlob = cv2.dnn.blobFromImage(img, scalefactor=0.00390625, size=(608, 608),swapRB=True ,crop=False);
textNet.setInput(inputBlob)
pred = textNet.forward()

cx = pred[:,0]*w
cy = pred[:,1]*h
xmin = cx - pred[:,2]*w/2
xmax = cx + pred[:,2]*w/2
ymin = cy - pred[:,3]*h/2
ymax = cy + pred[:,3]*h/2
scores = pred[:,4]
indx = np.where(scores>thresh)[0]
scores = scores[indx]
boxes = np.array(list(zip(xmin[indx],ymin[indx],xmax[indx],ymax[indx])))
print(boxes, scores)