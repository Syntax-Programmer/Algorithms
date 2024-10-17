#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int binary_search(int *arr, int low, int high, int target);
int linear_search(int *arr, int length, int target);
int jump_search(int *arr, int length, int target);
int exponential_search(int *arr, int length, int target);
int interpolation_search(int *arr, int length, int target);
int fibonacci_search(int *arr, int length, int target);

void quick_sort(int *arr, int low, int high);
void bubble_sort(int *arr, int length);

int binary_search(int *arr, int low, int high, int target) {
    int i;
    while (low <= high) {
        i = (high + low) / 2;
        if (arr[i] == target) return i;
        else if (arr[i] > target) high = i - 1;
        else low = i + 1;
    }
    printf("No such element found\n");
    return -1;
}

int linear_search(int *arr, int length, int target) {
    for (int i = 0; i < length; i++)
        if (arr[i] == target) return i;
    printf("No such element found\n");
    return -1;
}

int jump_search(int *arr, int length, int target) {
    int step = sqrt(length);
    int prev = 0;
    for (int i = 0; i < length; i += step) {
        if (arr[i] == target) return i;
        else if (arr[i] > target) {
            for (; prev < i; prev++)
                if (arr[prev] == target) return prev;
            printf("No such element found\n");
            return -1;
        }
        prev = i;
    }
    for (; prev < length; prev++) {
        if (arr[prev] == target) {
            return prev;
        }
    }
    printf("No such element found\n");
    return -1;
}

int exponential_search(int *arr, int length, int target) {
    if (arr[0] == target) return 0;
    int i = 1;
    while (i < length && arr[i] <= target) {
        if (arr[i] == target) return i;
        i *= 2;
    }
    return binary_search(arr, i / 2, fmin(length, i) - 1, target);
}

int interpolation_search(int *arr, int length, int target) {
    int high = length - 1;
    int low = 0;
    int probe;
    while(low <= high) {
        probe = low + ((high - low) * (target - arr[low])) / (arr[high] - arr[low]);
        if (arr[probe] == target) return probe;
        else if (arr[probe] > target) high = probe - 1;
        else low = probe + 1;
    }
    printf("No such element found\n");
    return -1;
}

int fibonacci_search(int *arr, int length, int target) {
    int fibo1 = 0;
    int fibo2 = 1;
    int nfibo = fibo1 + fibo2;
    while (nfibo < length) {
        fibo1 = fibo2;
        fibo2 = nfibo;
        nfibo = fibo1 + fibo2;
    }
    int offset = -1;
    int i;
    while (nfibo > 1) {
        i = fmin(fibo1 + offset, length - 1);
        if (arr[i] == target) return i;
        else if (arr[i] > target) {
            nfibo = fibo1;
            fibo2 = fibo2 - fibo1;
            fibo1 = nfibo - fibo2;
        } else {
            nfibo = fibo2;
            fibo2 = fibo1;
            fibo1 = nfibo - fibo2;
            offset = i;
        }
    }
    if (fibo1 && arr[offset + 1] == target) return offset + 1;
    printf("No such element found\n");
    return -1;
}

void quick_sort(int *arr, int low, int high) {
    if (high > low) {
        int pivot = arr[high];
        int temp;
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        quick_sort(arr, low, i);
        quick_sort(arr, i + 2, high);
    }
}

void bubble_sort(int *arr, int length) {
    int temp;
    for (int i = 0; i < length; i++)
        for (int j = 0; j < length - 1 - i; j++) // This is an improved bubble sort that ignores all elem that are sorted.
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

int main() {
    int arr[500] = {70, 66, 682, 817, 21, 816, 394, 542, 813, 860, 176, 972, 417, 987, 284, 926, 107, 602, 671, 921, 790, 535, 753, 124, 480, 754, 906, 252, 836, 317, 392, 511, 375, 797, 529, 34, 833, 215, 335, 962, 800, 905, 553, 909, 613, 402, 818, 612, 22, 343, 360, 823, 803, 886, 487, 332, 414, 473, 129, 565, 842, 621, 812, 104, 61, 50, 678, 953, 904, 238, 548, 2, 984, 881, 481, 4, 847, 362, 857, 723, 750, 276, 917, 500, 477, 521, 585, 401, 675, 732, 576, 740, 437, 190, 261, 666, 611, 986, 443, 273, 649, 711, 44, 674, 235, 404, 114, 968, 727, 194, 584, 311, 146, 419, 815, 858, 846, 717, 159, 595, 523, 567, 12, 638, 37, 963, 712, 165, 982, 725, 90, 787, 171, 313, 751, 641, 770, 321, 364, 583, 985, 203, 471, 894, 644, 349, 844, 760, 248, 569, 286, 702, 497, 645, 426, 111, 522, 908, 627, 724, 413, 1000, 428, 366, 39, 327, 875, 515, 804, 637, 251, 141, 870, 854, 65, 776, 733, 841, 265, 271, 550, 743, 814, 43, 774, 270, 513, 728, 685, 38, 701, 334, 490, 566, 182, 837, 56, 304, 761, 935, 116, 162, 862, 879, 737, 160, 622, 655, 919, 586, 493, 372, 253, 692, 757, 122, 52, 133, 138, 589, 795, 274, 342, 373, 764, 247, 387, 440, 834, 468, 315, 840, 308, 214, 458, 67, 587, 936, 20, 424, 472, 955, 507, 263, 990, 32, 172, 237, 486, 226, 35, 408, 626, 517, 23, 729, 233, 288, 300, 874, 11, 665, 661, 246, 922, 357, 5, 272, 378, 784, 697, 635, 125, 467, 96, 768, 491, 551, 485, 759, 689, 708, 180, 358, 390, 872, 383, 365, 498, 314, 53, 882, 980, 453, 484, 41, 232, 442, 850, 137, 381, 139, 370, 650, 290, 218, 977, 670, 181, 913, 250, 281, 64, 395, 416, 989, 778, 741, 293, 298, 876, 157, 287, 928, 501, 730, 680, 106, 447, 435, 503, 78, 524, 993, 568, 659, 115, 412, 482, 931, 85, 316, 355, 979, 777, 957, 958, 898, 224, 478, 647, 310, 151, 320, 384, 452, 865, 873, 427, 376, 668, 807, 863, 499, 809, 938, 82, 578, 629, 907, 446, 742, 831, 540, 654, 354, 843, 973, 210, 880, 570, 706, 86, 97, 707, 255, 6, 241, 40, 819, 625, 910, 925, 89, 924, 510, 95, 793, 556, 559, 564, 323, 662, 479, 694, 679, 599, 45, 946, 163, 113, 198, 933, 463, 883, 632, 745, 201, 51, 537, 444, 859, 223, 319, 220, 792, 338, 239, 432, 808, 58, 562, 703, 598, 386, 168, 28, 547, 423, 577, 835, 69, 99, 518, 941, 726, 912, 483, 211, 512, 296, 901, 415, 149, 278, 227, 242, 738, 934, 954, 204, 352, 466, 169, 509, 14, 821, 720, 109, 669, 773, 691, 878, 295, 975, 16, 765, 502, 825, 805, 3, 254, 657, 716, 762, 869, 756, 944, 63, 700, 57, 8, 572, 341, 961, 991, 781, 155, 789, 714};
    quick_sort(arr, 0, 499);
    for (int i = 0; i < 500; i++) {
        printf("%d \n", arr[i]);
    }
    int i = binary_search(arr, 0, 499, 714);
    printf("%d", i);
}
