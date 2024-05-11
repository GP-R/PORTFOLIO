using UnityEngine;
using UnityEngine.UI;
using TMPro;
using UnityEngine.EventSystems;

public class DialogueToggle : MonoBehaviour
{
    [SerializeField] private Toggle toggle = default;
    public Toggle Toggle { get => toggle; }

    [SerializeField] private TMP_Text toggleText = default;
    [SerializeField] private Image toggleImage = default;
    [SerializeField] private Sprite onToggleSprite = default;
    [SerializeField] private Sprite offToggleSprite = default;

    private void Start()
    {
        toggle.onValueChanged.AddListener(OnToggle);
    }

    public void OnToggle(bool value)
    {
        if(value)
        {
            toggleText.color = new Color32(0, 255, 123, 255);
            toggleImage.sprite = onToggleSprite;
        }
        else
        {
            toggleText.color = new Color32(176, 176, 176, 255);
            toggleImage.sprite = offToggleSprite;
        }
        EventSystem.current.SetSelectedGameObject(null);
    }
}
