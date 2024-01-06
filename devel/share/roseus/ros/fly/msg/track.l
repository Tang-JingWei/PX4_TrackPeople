;; Auto-generated. Do not edit!


(when (boundp 'fly::track)
  (if (not (find-package "FLY"))
    (make-package "FLY"))
  (shadow 'track (find-package "FLY")))
(unless (find-package "FLY::TRACK")
  (make-package "FLY::TRACK"))

(in-package "ROS")
;;//! \htmlinclude track.msg.html


(defclass fly::track
  :super ros::object
  :slots (_track_flag _track_cx _track_cy ))

(defmethod fly::track
  (:init
   (&key
    ((:track_flag __track_flag) 0)
    ((:track_cx __track_cx) 0)
    ((:track_cy __track_cy) 0)
    )
   (send-super :init)
   (setq _track_flag (round __track_flag))
   (setq _track_cx (round __track_cx))
   (setq _track_cy (round __track_cy))
   self)
  (:track_flag
   (&optional __track_flag)
   (if __track_flag (setq _track_flag __track_flag)) _track_flag)
  (:track_cx
   (&optional __track_cx)
   (if __track_cx (setq _track_cx __track_cx)) _track_cx)
  (:track_cy
   (&optional __track_cy)
   (if __track_cy (setq _track_cy __track_cy)) _track_cy)
  (:serialization-length
   ()
   (+
    ;; uint8 _track_flag
    1
    ;; uint8 _track_cx
    1
    ;; uint8 _track_cy
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _track_flag
       (write-byte _track_flag s)
     ;; uint8 _track_cx
       (write-byte _track_cx s)
     ;; uint8 _track_cy
       (write-byte _track_cy s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _track_flag
     (setq _track_flag (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _track_cx
     (setq _track_cx (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _track_cy
     (setq _track_cy (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get fly::track :md5sum-) "494b58be0cfd5a0309521cf7e47b2c2e")
(setf (get fly::track :datatype-) "fly/track")
(setf (get fly::track :definition-)
      "uint8 track_flag
uint8 track_cx
uint8 track_cy

")



(provide :fly/track "494b58be0cfd5a0309521cf7e47b2c2e")


