Sa=[3];
Sb=[5];
s=[3;5];  % the point in a plane is represented by a column vector.
n=2*randn(2,100); % Create a 100-sample noise sequence with a standard deviation of 2.
x=zeros(2,100);
for (i=1:100)
    x(:,i)=s+n(:,i);  % Add the noise to the true state to create 100 observations of the true state.
    plot(x(1,i),x(2,i),'k.');
end;
L=length(Sa);
Pr=ones(L,L); % Initialize the table to all ones
Po=ones(L,L);
Pr=Pr/sum(sum(Pr)); % Turn the table into a pmf by dividing by the sum.
Po=Po/sum(sum(Po)); % Each value is now 1/9.
K=[4,0;0,4]; % covariance matrix.
m=0*Pr;
for (i=1:length(Pr))  % For each entry in my prior table.
    for (j=1:length(Pr))
        me=[Sa(i);Sb(j)]
        m(i,j) = 1/sqrt((2*pi)^2*det(K)) * exp(-(x(:,1)-me)'*inv(K)*(x(:,1)-me)/2) % Compute likelihood
        m(i,j) = m(i,j) * Pr(i,j) % Combine with prior
    end;
end;
Po=m/sum(sum(m))
[Pr,Po]
[a,b]=find(Po==max(max(Po)))  % Pull out the indices at which Po achieves its max.
sest=[Sa(a);Sb(b)]  % The best estimate of the true state.

return 
figure(3); % Switch to a new figure window.
[a,b]=find(Po==max(max(Po)));  % Pull out the indices at which Po achieves its max.
sest=[Sa(a);Sb(b)];  % The best estimate of the true state.
subplot(211); plot(1,sest(1)); hold on;
line([1,100],[s(1),s(1)]); % Draw a line at the location of the x component.
subplot(212); plot(1,sest(2)); hold on;
line([1,100],[s(2),s(2)]); % Draw a line at the location of the y component.
for (n=2:length(x));
    Pr=Po;
    m=0*Pr;
	for (i=1:length(Pr))  % For each entry in my prior table.
        for (j=1:length(Pr))
            me=[Sa(i);Sb(j)];
            m(i,j) = 1/sqrt((2*pi)^2*det(K)) * exp(-(x(:,n)-me)'*inv(K)*(x(:,n)-me)/2); %Compute likelihood
            m(i,j) = m(i,j) * Pr(i,j); % Combine with prior    
        end;
	end;
	Po=m/sum(sum(m));
    [a,b]=find(Po==max(max(Po)));  % Pull out the indices at which Po achieves its max.
    sest=[Sa(a);Sb(b)];  % The best estimate of the true state.
    subplot(211);plot(n,sest(1),'k.');
    subplot(212); plot(n,sest(2),'k.');
end;   
subplot(211); hold off;
subplot(212); hold off;