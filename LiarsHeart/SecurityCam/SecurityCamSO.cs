using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "new SecurityCam Data", menuName = "SecurityCam/SecurityCam")]
public class SecurityCamSO : ItemSO
{
    [SerializeField] private List<DateBySecurityCam> dateBySecurityCams = new List<DateBySecurityCam>();
    public List<DateBySecurityCam> DateBySecurityCams { get => dateBySecurityCams; }

    public List<ImageByTime> GetDateToImageByTimes(string date)
    {
        foreach(DateBySecurityCam data in dateBySecurityCams)
        {
            if(data.Date == date)
            {
                return data.ImageByTimes;
            }
        }

        return null;
    }
}

[System.Serializable]
public class DateBySecurityCam
{
    [SerializeField] private string date;
    public string Date { get => date; }

    [SerializeField] private List<ImageByTime> imageByTimes = new List<ImageByTime>();
    public List<ImageByTime> ImageByTimes { get => imageByTimes; }
}

[System.Serializable]
public class ImageByTime
{
    [SerializeField] private string time;
    public string Time { get => time; }

    [SerializeField] private Sprite spriteImage;
    public Sprite SpriteImage { get => spriteImage; }
}