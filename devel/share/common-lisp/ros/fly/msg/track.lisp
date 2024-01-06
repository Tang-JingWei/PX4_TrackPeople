; Auto-generated. Do not edit!


(cl:in-package fly-msg)


;//! \htmlinclude track.msg.html

(cl:defclass <track> (roslisp-msg-protocol:ros-message)
  ((track_flag
    :reader track_flag
    :initarg :track_flag
    :type cl:fixnum
    :initform 0)
   (track_cx
    :reader track_cx
    :initarg :track_cx
    :type cl:fixnum
    :initform 0)
   (track_cy
    :reader track_cy
    :initarg :track_cy
    :type cl:fixnum
    :initform 0))
)

(cl:defclass track (<track>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <track>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'track)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name fly-msg:<track> is deprecated: use fly-msg:track instead.")))

(cl:ensure-generic-function 'track_flag-val :lambda-list '(m))
(cl:defmethod track_flag-val ((m <track>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader fly-msg:track_flag-val is deprecated.  Use fly-msg:track_flag instead.")
  (track_flag m))

(cl:ensure-generic-function 'track_cx-val :lambda-list '(m))
(cl:defmethod track_cx-val ((m <track>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader fly-msg:track_cx-val is deprecated.  Use fly-msg:track_cx instead.")
  (track_cx m))

(cl:ensure-generic-function 'track_cy-val :lambda-list '(m))
(cl:defmethod track_cy-val ((m <track>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader fly-msg:track_cy-val is deprecated.  Use fly-msg:track_cy instead.")
  (track_cy m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <track>) ostream)
  "Serializes a message object of type '<track>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'track_flag)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'track_cx)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'track_cy)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <track>) istream)
  "Deserializes a message object of type '<track>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'track_flag)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'track_cx)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'track_cy)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<track>)))
  "Returns string type for a message object of type '<track>"
  "fly/track")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'track)))
  "Returns string type for a message object of type 'track"
  "fly/track")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<track>)))
  "Returns md5sum for a message object of type '<track>"
  "494b58be0cfd5a0309521cf7e47b2c2e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'track)))
  "Returns md5sum for a message object of type 'track"
  "494b58be0cfd5a0309521cf7e47b2c2e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<track>)))
  "Returns full string definition for message of type '<track>"
  (cl:format cl:nil "uint8 track_flag~%uint8 track_cx~%uint8 track_cy~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'track)))
  "Returns full string definition for message of type 'track"
  (cl:format cl:nil "uint8 track_flag~%uint8 track_cx~%uint8 track_cy~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <track>))
  (cl:+ 0
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <track>))
  "Converts a ROS message object to a list"
  (cl:list 'track
    (cl:cons ':track_flag (track_flag msg))
    (cl:cons ':track_cx (track_cx msg))
    (cl:cons ':track_cy (track_cy msg))
))
