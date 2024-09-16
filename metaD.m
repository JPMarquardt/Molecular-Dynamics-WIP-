Ir = 1000;
i = 1:2001;
x = i2x((1:(2*Ir+1)),Ir);
G0 = (x + 0.5).^2.*(x-0.5).^2;
x0 = -0.5;
startingPos = {x0,G0};

nu = updatepos(startingPos);

p = plot(nan,nan);
hold on;
q = plot(nan,nan,'r.');
p.XData = x;
xval2 = -0.5;
xlabel('CV')
ylabel('Energy (a.u.)')

for n = 1:1000

    nu = updatepos(nu);
    xval = nu{1};
    ival = x2i(xval,Ir);
    PW = nu{2};
    p.YData = PW;
    q.YData = PW(ival);
    q.XData = xval;
    
    

    exportgraphics(gcf,'testAnimated.gif','Append',true);
    if xval2 > 0
        break
    end
    xval2 = xval;
end
hold off;

%%
figure;
plot(x,PW,'cyan-')
hold on;
plot(x,PW-G0,'k-')
[val,ind] = max(PW-G0)
plot(x(ind),val,'r.')
plot(x,G0,'b-')
xlabel('CV')
ylabel('Energy (a.u.)')
hold off;



%%
function Y = SSkernel(x,Y0)
    x2 = (x-min(x))/(max(x)-min(x));
    Y = Y0*(30*(x2).^4 - 60*(x2).^3 + 30*(x2).^2);
end

function i = x2i(x,Ir)
    i = x*Ir + Ir + 1;
end
function x = i2x(i,Ir)
    x = (i - 1 - Ir)/Ir;
end
function oupS = updatepos(inpS)
    x0 = inpS{1};
    PW = inpS{2};
    ir = 100; %not optimized for odd
    Ir = 1000;
    i = x2i(x0,Ir);
    kT = 0.01;
    h = 0.001;


    if i < ir/2
        ipts = 1:(ir+1);
    elseif i > (2*Ir-ir/2)
        ipts = 2*Ir+2-(1:(ir+1));
    else
        ipts = (1:(ir+1)) - (ir/2 + 1) + i;
    end

    xpts = i2x(ipts,Ir);
    ES = PW(ipts);
    propS = exp(-ES/kT);
    pS = propS/sum(propS);
    cdf = zeros(1,ir+1);
    cdf(1) = pS(1);
    for j = 1:ir
        cdf(j+1) = cdf(j) + pS(j+1);
    end
    samp = rand(1);
    inu = find( cdf > samp, 1 ) + min(ipts) - 1;
    xnu = i2x(inu, Ir);
    
    PWnu = PW;
    PWnu(ipts) = ES + SSkernel(xpts,h);


    oupS = {xnu,PWnu};

end