pt = 'F:\\MIT\\MIT\\pos_one_person\\';
mt= 'F:\MIT\MIT\channel\positive\pos_edge_robinson_45_524\'
ext = '*.bmp';
dis = dir([pt ext]);
nms = {dis.name};

for k = 1:1:524
    nm = [pt nms{k}];
    mm=[mt nms{k}];
    I = imread(nm);

    I=im2double(I); 
    [height width R]=size(I); 
 
%Dx=[-1 -2 -1 
    %0   0  0 
    %1   2  1]; 
 
%Dy=[-1 0 1 
    %-2 0 2  
    %-1 0 1]; 
 
    for i=2:height-1
        for j=2:width-1 
            Dx(i,j)=[I(i+1,j-1)-I(i-1,j-1)]+2*[I(i+1,j)-I(i-1,j)]+[I(i+1,j+1)-I(i-1,j+1)]; 
            Dy(i,j)=[I(i-1,j+1)-I(i-1,j-1)]+2*[I(i,j+1)-I(i,j-1)]+[I(i+1,j+1)-I(i+1,j-1)]; 
            S(i,j)=sqrt(Dx(i,j)^2+Dy(i,j)^2); 
            if Dx(i,j)<1 
                Dx(i,j)=0; 
            else Dx(i,j)=1; 
            end 
        end 
    end 
%     figure(1); 
%     imshow(S,[]);
    imwrite(S,mm)
end


% % I=imread('F:\MIT\MIT\positive\1.bmp');
% % I=im2double(I); 
% % %figure; 
% % %imshow(I);title('org img'); 
% %  
% % [height width R]=size(I); 
% %  
% % %Dx=[-1 -2 -1 
% %     %0   0  0 
% %     %1   2  1]; 
% %  
% % %Dy=[-1 0 1 
% %     %-2 0 2  
% %     %-1 0 1]; 
% %  
% % for i=2:height-1
% %     for j=2:width-1 
% %         Dx(i,j)=[I(i+1,j-1)-I(i-1,j-1)]+2*[I(i+1,j)-I(i-1,j)]+[I(i+1,j+1)-I(i-1,j+1)]; 
% %         Dy(i,j)=[I(i-1,j+1)-I(i-1,j-1)]+2*[I(i,j+1)-I(i,j-1)]+[I(i+1,j+1)-I(i+1,j-1)]; 
% %         S(i,j)=sqrt(Dx(i,j)^2+Dy(i,j)^2); 
% %         if Dx(i,j)<1 
% %             Dx(i,j)=0; 
% %         else Dx(i,j)=1; 
% %         end 
% %     end 
% % end 
% % figure(1); 
% % imshow(S,[]);%x???????? 
% % imwrite(S,'G:\robinson45\123.bmp')
% % % figure(2); 
% % % imshow(Dy,[]);%y???????? 
% % %  
% % %  
 
