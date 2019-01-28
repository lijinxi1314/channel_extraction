
% clear;clc;close all;
% image = imread('D:\pos\4.bmp');
% image = im2double(image(:,:,1));
% 
% tic;
% H1 = fspecial('gaussian',5,5);
% H2 = fspecial('gaussian',5,15);
% dog = H1 - H2;
% dogFilterImage1 = conv2(image,dog,'same');
% toc
% imwrite(mat2gray(dogFilterImage1),'D:\pos\4_1.bmp')


file_path =  'D:\pos\positive\';
%out_path='D:\output\'
img_path_list = dir(strcat(file_path,'*.bmp'));
img_num = length(img_path_list);
if img_num > 0 
        for j = 1:img_num 
            image_name_dog = strcat('dog',img_path_list(j).name)
            image_name = img_path_list(j).name;
            image =  imread(strcat(file_path,image_name));
            fprintf(' %d %s\n',j,strcat(file_path,image_name));
            
            image = im2double(image(:,:,1));
            H1 = fspecial('gaussian',5,5);
            H2 = fspecial('gaussian',5,15);
            dog = H1 - H2;
            dogFilterImage1 = conv2(image,dog,'same');
            imwrite(mat2gray(dogFilterImage1),strcat(file_path,image_name_dog))
        end
end
