function fast_plot(varargin)

[ax,args] = axescheck(varargin{:});

[x,y] = deal(args{:});

ax = newplot(ax);

set(ax,'XMinorGrid','on');
set(ax,'YMinorGrid','on');

if ~ishold(ax)
  [minx,maxx] = minmax(x);
  [miny,maxy] = minmax(y);
  axis(ax,[minx maxx miny maxy])
end

cur_sgt = line('linestyle','-','erase','xor','xdata',x(1),'ydata',y(1));
trace = line('linestyle','-','erase','none','xdata',[],'ydata',[]);

m = length(x);

for i = 2:m
    j = i-1:i;
        set(cur_sgt,'xdata',x(i),'ydata',y(i))
        set(trace,'xdata',x(j),'ydata',y(j))
        drawnow
end
end

function [minx,maxx] = minmax(x)
minx = min(x(isfinite(x)));
maxx = max(x(isfinite(x)));
if minx == maxx
  minx = maxx-1;
  maxx = maxx+1;
end
end