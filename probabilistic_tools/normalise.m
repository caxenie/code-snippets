function fxy=normalise(fin)

sum=0;
[xsize,ysize]=size(fin);
fxy=zeros(xsize,ysize);
for i=1:xsize
   for j=1:ysize
      sum=sum+fin(i,j);
   end
end
area=1; % hack
% now normalise 
for i=1:xsize
   for j=1:ysize
      fxy(i,j)=fin(i,j)*(area/sum);
   end
end
