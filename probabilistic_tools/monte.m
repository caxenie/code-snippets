ii=0;
data;
pos=bayes(like1,prior,1);
while (pos(1)<0.999)
   ii=ii+1
   temp=rand;
   
   mi1=mutualinfo(like1,pos);
   mi2=mutualinfo(like2,pos);
   if(mi1>mi2)
   %if(rand<0.5)
   if (temp<0.1)
      obs=3;
   elseif (temp<0.55)
      obs=2;
   else
      obs=1;
   end
      pos=bayes(like1,pos,obs);
   else
   if (temp<0.45)
      obs=3;
   elseif (temp<0.55)
      obs=2;
   else
      obs=1;
   end
      pos=bayes(like2,pos,obs);
   end
   
end
