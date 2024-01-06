;; Auto-generated. Do not edit!


(when (boundp 'object_detect::Person)
  (if (not (find-package "OBJECT_DETECT"))
    (make-package "OBJECT_DETECT"))
  (shadow 'Person (find-package "OBJECT_DETECT")))
(unless (find-package "OBJECT_DETECT::PERSON")
  (make-package "OBJECT_DETECT::PERSON"))

(in-package "ROS")
;;//! \htmlinclude Person.msg.html


(defclass object_detect::Person
  :super ros::object
  :slots (_detect_flag _cx _cy _dx _dy ))

(defmethod object_detect::Person
  (:init
   (&key
    ((:detect_flag __detect_flag) 0)
    ((:cx __cx) 0)
    ((:cy __cy) 0)
    ((:dx __dx) 0)
    ((:dy __dy) 0)
    )
   (send-super :init)
   (setq _detect_flag (round __detect_flag))
   (setq _cx (round __cx))
   (setq _cy (round __cy))
   (setq _dx (round __dx))
   (setq _dy (round __dy))
   self)
  (:detect_flag
   (&optional __detect_flag)
   (if __detect_flag (setq _detect_flag __detect_flag)) _detect_flag)
  (:cx
   (&optional __cx)
   (if __cx (setq _cx __cx)) _cx)
  (:cy
   (&optional __cy)
   (if __cy (setq _cy __cy)) _cy)
  (:dx
   (&optional __dx)
   (if __dx (setq _dx __dx)) _dx)
  (:dy
   (&optional __dy)
   (if __dy (setq _dy __dy)) _dy)
  (:serialization-length
   ()
   (+
    ;; uint8 _detect_flag
    1
    ;; uint8 _cx
    1
    ;; uint8 _cy
    1
    ;; uint8 _dx
    1
    ;; uint8 _dy
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _detect_flag
       (write-byte _detect_flag s)
     ;; uint8 _cx
       (write-byte _cx s)
     ;; uint8 _cy
       (write-byte _cy s)
     ;; uint8 _dx
       (write-byte _dx s)
     ;; uint8 _dy
       (write-byte _dy s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _detect_flag
     (setq _detect_flag (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _cx
     (setq _cx (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _cy
     (setq _cy (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _dx
     (setq _dx (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _dy
     (setq _dy (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get object_detect::Person :md5sum-) "d4493f50035a5d649cf03c09f9d7953f")
(setf (get object_detect::Person :datatype-) "object_detect/Person")
(setf (get object_detect::Person :definition-)
      "uint8 detect_flag
uint8 cx
uint8 cy 
uint8 dx	
uint8 dy	
")



(provide :object_detect/Person "d4493f50035a5d649cf03c09f9d7953f")


