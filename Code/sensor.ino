void scale_setup() {
  scale0.begin(scale0_clk, scale0_data);      // Scale begin
  scale1.begin(scale1_clk, scale1_data);
  scale2.begin(scale2_clk, scale2_data);
  
  loop_timer = micros();
  //ota(); 
}
