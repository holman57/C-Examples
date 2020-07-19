double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size){
    
    
    int odd = (nums1Size + nums2Size) % 2;
    int mid = ((nums1Size + nums2Size) / 2);
    
    int i, j, prev;
    i = 0;
    j = 0;
    
    
    while (i < nums1Size && j < nums2Size){
        if (i + j == mid){
            if (odd == 1){
                if (nums1[i] < nums2[j]){
                    return nums1[i];
                }
                else 
                {
                    return nums2[j];
                }
            }
            else
            {
                if (nums1[i] < nums2[j]){
                    return (float)(nums1[i] + prev)/2;
                }
                else{
                    return (float)(nums2[j] + prev)/2;
                }
            }
        }
        
        else if (nums1[i] < nums2[j]){
            prev = nums1[i];
            i++;
        }
        else{
            prev = nums2[j];
            j++;
        }
    }
    
    while (i < nums1Size){
        if (i + j == mid){
            if (odd == 1){
                return nums1[i];
            }
            else
            {
                return (float)(nums1[i] + prev)/2;
            }
        }
        prev = nums1[i];
        i++;
    }
    
    while (j < nums2Size){
        if (i + j == mid){
            if (odd == 1){
                return nums2[j];
            }
            else
            {
                return (float)(nums2[j] + prev)/2;
            }
        }
        prev = nums2[j];
        j++; 
    }
    return 0;
}