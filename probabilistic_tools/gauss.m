function [fxy,x,y]=gauss(mx,my,sigmax,sigmay,rhoxy)
% function to generate a gaussian mesh
% fxy=gauss(mx,my,sigmax,sigmay,rhoxy)

% set up range for x and y
dx=1;
dy=1;
x=0:dx:63;
y=0:dy:63;
area=dx*dy;

cov=[sigmax^2, sigmax*sigmay*rhoxy; sigmax*sigmay*rhoxy, sigmay^2];
icov=inv(cov);
cx=x-mx;
cy=y-my;
[nul,xsize]=size(x);
[nul,ysize]=size(y);

sum=0;
fxy=zeros(xsize,ysize);
for i=1:xsize
   for j=1:ysize
      fxy(i,j)=exp(-[cx(i) cy(j)]*icov*[cx(i); cy(j)]/2);
      sum=sum+fxy(i,j);
   end
end

% now normalise (may not want this here)
for i=1:xsize
   for j=1:ysize
      fxy(i,j)=fxy(i,j)*(area/sum);
   end
end
