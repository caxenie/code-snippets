function mi=mutualinfo(like,prior)
%
% mi=mutualinfo(like,prior)

% function to compute mutual information gain
% from a prior (a column vector of length N)
% and a likelihood matrix (a matrix of N rows and M columns
%


[temp,N]=size(prior);
[N,M]=size(like);

joint=zeros(N,M);
pz=zeros(M,1);
%
% first compute the joint probability density
for i=1:N
   joint(i,:)=like(i,:)*prior(i);
end

% this should sum to 1
scale=sum(sum(joint));
joint=joint/scale;

% now compute the observation distribution by summing over x
pz=sum(joint,1);

% observation entropy is expected value of pz
enz=sum(pz.*log(pz));

% conditional entropy is the expected value of the likelihood
enzx=sum(sum(joint.*log(like)));

% the information gain is now the difference
mi=enzx-enz;

