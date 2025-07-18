#include "servo.h"

void servo_init(servo_t* srv, uint8_t pin) {
    srv->pin = pin;
    srv->current_angle = 90;  // Góc mặc định ở giữa
    srv->target_angle = 90;
    srv->last_update_time = 0;
    srv->attached = false;
}

void servo_attach(servo_t* srv) {
    if (!srv->attached) {
        pinMode(srv->pin, OUTPUT);
        srv->attached = true;
        
        // Đặt servo về vị trí mặc định
        servo_write_angle(srv, srv->current_angle);
    }
}

void servo_detach(servo_t* srv) {
    if (srv->attached) {
        digitalWrite(srv->pin, LOW);
        srv->attached = false;
    }
}

void servo_write_angle(servo_t* srv, uint16_t angle) {
    if (!srv->attached) return;
    
    // Giới hạn góc trong khoảng cho phép
    if (angle > SERVO_MAX_ANGLE) {
        angle = SERVO_MAX_ANGLE;
    }
    
    // Chuyển đổi góc sang độ rộng xung
    uint16_t pulse_width = map(angle, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE, 
                              SERVO_MIN_PULSE_WIDTH, SERVO_MAX_PULSE_WIDTH);
    
    servo_write_microseconds(srv, pulse_width);
    srv->current_angle = angle;
}

void servo_write_microseconds(servo_t* srv, uint16_t microseconds) {
    if (!srv->attached) return;
    
    // Giới hạn độ rộng xung
    if (microseconds < SERVO_MIN_PULSE_WIDTH) {
        microseconds = SERVO_MIN_PULSE_WIDTH;
    }
    if (microseconds > SERVO_MAX_PULSE_WIDTH) {
        microseconds = SERVO_MAX_PULSE_WIDTH;
    }
    
    // Tạo xung PWM thủ công
    digitalWrite(srv->pin, HIGH);
    delayMicroseconds(microseconds);
    digitalWrite(srv->pin, LOW);
    delayMicroseconds(SERVO_REFRESH_INTERVAL - microseconds);
}

uint16_t servo_read_angle(servo_t* srv) {
    return srv->current_angle;
}

bool servo_is_attached(servo_t* srv) {
    return srv->attached;
}

void servo_update(servo_t* srv) {
    if (!srv->attached) return;
    
    unsigned long current_time = millis();
    
    // Cập nhật vị trí servo mỗi 20ms (50Hz)
    if (current_time - srv->last_update_time >= 20) {
        if (srv->current_angle != srv->target_angle) {
            // Di chuyển từ từ về vị trí đích
            if (srv->current_angle < srv->target_angle) {
                srv->current_angle++;
            } else {
                srv->current_angle--;
            }
            
            servo_write_angle(srv, srv->current_angle);
        }
        
        srv->last_update_time = current_time;
    }
}

void servo_move_to(servo_t* srv, uint16_t target_angle, uint16_t speed) {
    if (!srv->attached) return;
    
    // Giới hạn góc đích
    if (target_angle > SERVO_MAX_ANGLE) {
        target_angle = SERVO_MAX_ANGLE;
    }
    
    srv->target_angle = target_angle;
    
    if (speed == 0) {
        // Di chuyển ngay lập tức
        servo_write_angle(srv, target_angle);
    } else {
        // Di chuyển từ từ - sẽ được xử lý trong servo_update()
        // Speed parameter có thể được sử dụng để điều chỉnh tốc độ trong tương lai
    }
} 