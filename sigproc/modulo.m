filtro;
M=zeros(length(data),1);
alfa=zeros(length(data),1);%angulo entre x e y
beta=zeros(length(data),1);%angulo entre x e z
for i= 1:length(data);
  M(i)=sqrt(sumsq(data(i,1:3)));
  alfa(i)=atan(data(i,2)/data(i,1));
  beta(i)=atan(data(i,3)/data(i,1));
end
subplot(2,1,1);plot(M,'LineWidth',4);


subplot(2,1,2);%plot((180/pi)*[alfa beta]); hold on;
plot((180/pi)*([alfa beta]-[mean(alfa(1:10)) mean(beta(1:10))])); grid on;
mean(M);
