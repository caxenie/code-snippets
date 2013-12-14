mx=20;
my=10;
sigmax=6;
sigmay=5;
rho=0;
[fxy1,x,y]=gauss(mx,my,sigmax,sigmay,rho);
mx=25;
my=25;
sigmax=10;
sigmay=8;
rho=0.1;
[fxy2,x,y]=gauss(mx,my,sigmax,sigmay,rho);

fprior=fxy1+fxy2;

figure(1)
surf(x,y,fprior);
shading interp;
view(-20, 60);
colormap(hsv);
xlabel('X Range (km)');
ylabel('Y Range (km)');
title('Prior Location Density');

mx=25;
my=18;
sigmax=10;
sigmay=1;
rho=0.9;
[flike1,x,y]=gauss(mx,my,sigmax,sigmay,rho);

figure(2)
surf(x,y,flike1);
shading interp;
view(-20, 60);
colormap(hsv);
xlabel('X Range (km)');
ylabel('Y Range (km)');
title('Location likelihood from Sensor 1');

fposterior1=flike1.*fprior;
fposterior1=normalise(fposterior1);
figure(3)
surf(x,y,fposterior1);
shading interp;
view(-20, 60);
colormap(hsv);
xlabel('X Range (km)');
ylabel('Y Range (km)');
title('Posterior location density after one observation from sensor 1');

fposterior2=flike1.*fposterior1;
fposterior2=normalise(fposterior2);
figure(4)
surf(x,y,fposterior2);
shading interp;
view(-20, 60);
colormap(hsv);
xlabel('X Range (km)');
ylabel('Y Range (km)');
title('Posterior location density after two observations from sensor 1');

mx=25;
my=18;
sigmax=1;
sigmay=10;
rho=-0.9;
[flike2,x,y]=gauss(mx,my,sigmax,sigmay,rho);

figure(5)
surf(x,y,flike2);
shading interp;
view(-20, 60);
colormap(hsv);
xlabel('X Range (km)');
ylabel('Y Range (km)');
title('Location likelihood from Sensor 2');

fposterior3=flike2.*fposterior2;
fposterior3=normalise(fposterior3);
figure(6)
surf(x,y,fposterior3);
shading interp;
view(-20, 60);
colormap(hsv);
xlabel('X Range (km)');
ylabel('Y Range (km)');
title('Posterior location density following update from sensor 2');






