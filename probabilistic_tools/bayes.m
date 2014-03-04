function posterior=bayes(like,prior,obs)
%
% posterior=bayes(like,prior,obs)
%
% like is an N*M array of N state, M observation likelihoods
% prior is an N dimensional vector of prior probabilities
% obs is the column (observation) of the likelihood to be used


% element by element update of prior
posterior=like(:,obs).*prior;

posterior=posterior/sum(posterior);


