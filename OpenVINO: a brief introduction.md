During me being a consultant of Furhat Robotics, the thing after building a tensorflow cnn model is to deploy such model in the robot. Since the robot has a limited computation
resourse, they suggested I use OpenVINO, a toolkit by Intel that can extends CV workload to all Intel hardwares. That was when I started to learn OpenVINO and realized what a powerful
yet lesser-known tool that is. The processing speed improvement is remarkable, which is very essential for a robot to do real time analysis with its tiny little cpu.

The idea behind this toolkit is pretty simple, which is to sacrifice a little accuracy in exchange for saving time and model storage space. Do not neglect the space saving feature, it
is not practicle to put a 300MB model inside the robot's 1GB disk just for one function. Rather if you can manage to decrease it to 50MB, that is something negotiable. 

The reason I write this article is that during the process of learning and testing this powerful toolkit on my own, I discovered that there are basically no articles for beginners 
on how to start using it besides official documentations, which in my opinion are not clear at all and not easy for one to quickly obtain the basic knowledge. Also there's no saying that 
I will use this toolkit in the future so it might be better for me to write them all down in case I need to review later on.

