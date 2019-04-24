# -*- coding:utf-8 -*-
__author__ = 'Saber'
__date__ = '26/3/19 下午5:00'

import time

from PyQt5.QtWidgets import QLabel
from PyQt5.QtGui import QPixmap, QBitmap
from PyQt5.QtCore import QThread, pyqtSignal, QMutex, QMutexLocker


from setting import face_img


class CommonHelper:
    def __init__(self):
        pass

    @staticmethod
    def readQss(style):
        with open(style, 'r', encoding='utf-8') as f:
            return f.read()


# def face_recog(known_face_encodings, known_face_names, frame):
#     """
#     :param known_face_encodings:
#     :param known_face_names:
#     :param frame:
#     :return: 验证未通过：Uknown,  通过返回name
#     """
#     # img_face_encoding = face_recognition.face_encodings(img)[0]
#
#     face_locations = []
#     # face_encodings = []
#     face_names = []
#     name = 'Uknown'
#     process_this_frame = True
#     lis = []
#     limite = ''
#
#     small_frame = cv2.resize(frame, (0, 0), fx=0.25, fy=0.25)
#     rgb_small_frame = small_frame[:, :, ::-1]
#
#     if process_this_frame:
#         face_locations = face_recognition.face_locations(rgb_small_frame)
#         face_encodings = face_recognition.face_encodings(rgb_small_frame, face_locations)
#         # print("face_encoding:",face_encodings)
#         face_names = []
#         for face_encoding in face_encodings:
#             matches = face_recognition.compare_faces(known_face_encodings, face_encoding, tolerance=0.39)
#             limite = 'Unauthorised'
#
#             # 获取匹配成功的名字
#             if True in matches:
#                 limite = 'Authorised'
#                 first_match_index = matches.index(True)
#                 name = known_face_names[first_match_index]
#
#             face_names.append(name)
#         process_this_frame = False
#
#     return name
#
#
# def face_login(frame):
#     """
#     人脸认证
#     :param frame:
#     :return:
#     """
#     cv2.cvtColor(frame, cv2.COLOR_BGR2RGB, frame)
#
#     user_info = select_user_info()
#
#     known_face_encodings = [i['user_face_info'] for i in user_info]
#     known_face_names = [i['user_name'] for i in user_info]
#     known_face_encodings = [np.array(eval(','.join(i.split()))) for i in known_face_encodings]
#     # known_face_encodings, known_face_names = load_img()
#     name = face_recog(known_face_encodings, known_face_names, frame)
#
#     return name


class Face_Label(QLabel):
    """
    定义人脸显示QLabel
    """
    def __init__(self, parent=None):
        super(Face_Label, self).__init__(parent=parent)

        # 获取图片size
        self.pixmap = QPixmap(face_img)
        self.resize(self.pixmap.size())
        # 设置mask
        self.setMask(QBitmap(self.pixmap.mask()))


class Timer(QThread):
    """
    定时线程, 定时发送信号
    """
    Camer = pyqtSignal()

    def __init__(self, parent=None):
        super(Timer, self).__init__(parent)
        self.stoped = False

        # 创建互斥信号量
        self.mutex = QMutex()

    def run(self):
        # 使用互斥信号量保护全局变量self.stoped
        # 同一时间只有一个线程可以访问
        with QMutexLocker(self.mutex):
            self.stoped = False
        while True:
            if self.stoped:
                return
            self.Camer.emit()
            #40毫秒发送一次信号
            time.sleep(0.1)

    def stop(self):
        with QMutexLocker(self.mutex):
            self.stoped = True

    def isStoped(self):
        with QMutexLocker(self.mutex):
            return self.stoped


