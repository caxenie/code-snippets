function en=entropy(P)
%
% en=entropy(P)
%
% function to compute the entropy associated with a distribution P
% the matrix P is assumed to be a conditional distribution with
% the columns of P being the state dimension


[nstates,nobs]=size(P);

en=zeros(1,nobs);

for i=1:nobs
   for j=1:nstates
      en(1,i)=en(1,i)-(P(j,i)*log(P(j,i)));
   end
end
