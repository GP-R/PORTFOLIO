using System;
using System.Collections;
using UnityEngine;
using UnityEngine.UI;

public class CameraFade
{
    private Image fadeImage;
    private Canvas fadeCanvas;
    private float fadeSpeed = 1.0f;
    public Coroutine curCoroutine = default;

    public CameraFade(Canvas canvas = null, Image image = null)
    {
        InitializeCanvas(canvas);
        InitializeImage(image);
    }

    private void InitializeCanvas(Canvas canvas)
    {
        if (canvas != null)
        {
            fadeCanvas = canvas;
            return;
        }

        GameObject canvasObject = new GameObject("FadeCanvas");
        fadeCanvas = canvasObject.AddComponent<Canvas>();
        fadeCanvas.renderMode = RenderMode.ScreenSpaceOverlay;
        fadeCanvas.sortingOrder = 1;

        CanvasScaler scaler = canvasObject.AddComponent<CanvasScaler>();
        scaler.uiScaleMode = CanvasScaler.ScaleMode.ScaleWithScreenSize;
        scaler.referenceResolution = new Vector2(Screen.width, Screen.height);

        canvasObject.AddComponent<GraphicRaycaster>();
    }

    private void InitializeImage(Image image)
    {
        if (image != null)
        {
            fadeImage = image;
            return;
        }

        GameObject imageObject = new GameObject("FadeImage");
        fadeImage = imageObject.AddComponent<Image>();
        imageObject.transform.SetParent(fadeCanvas.transform);

        fadeImage.color = new Color(0.0f, 0.0f, 0.0f, 0.0f);
        fadeImage.rectTransform.anchorMin = new Vector2(0.0f, 0.0f);
        fadeImage.rectTransform.anchorMax = new Vector2(1.0f, 1.0f);
        fadeImage.rectTransform.pivot = new Vector2(0.5f, 0.5f);
        fadeImage.rectTransform.position = fadeCanvas.transform.position;
        fadeImage.gameObject.SetActive(false);
    }

    public void Fade(MonoBehaviour monoBehaviour, float fadeDuration)
    {
        if(curCoroutine != null)
        {
            return;
        }

        curCoroutine = monoBehaviour.StartCoroutine(UpdateFade(monoBehaviour, fadeDuration));
    }

    public void Fade(MonoBehaviour monoBehaviour, float fadeDuration, Func<IEnumerator> func)
    {
        if (curCoroutine != null)
        {
            return;
        }

        curCoroutine = monoBehaviour.StartCoroutine(UpdateFade(monoBehaviour, fadeDuration, func));
    }

    public void FadeOut(MonoBehaviour monoBehaviour, float fadeDuration, bool fullScreenFade = true)
    {
        if (curCoroutine != null)
        {
            return;
        }

        if(!fullScreenFade)
        {
            fadeCanvas.sortingOrder = 0;
        }

        fadeCanvas.sortingOrder = 1;
        curCoroutine = monoBehaviour.StartCoroutine(UpdateFadeOut(fadeDuration));
    }

    public void FadeIn(MonoBehaviour monoBehaviour)
    {
        if (curCoroutine != null)
        {
            return;
        }

        curCoroutine = monoBehaviour.StartCoroutine(UpdateFadeIn());
    }

    private IEnumerator UpdateFadeOut(float fadeDuration)
    {
        fadeImage.gameObject.SetActive(true);
        Color tempColor = fadeImage.color;

        while (tempColor.a < 1.0f)
        {
            tempColor.a += Time.deltaTime / fadeSpeed;
            fadeImage.color = tempColor;
            yield return null;
        }
        fadeImage.color = tempColor;

        yield return new WaitForSeconds(fadeDuration);
        End();
    }

    private IEnumerator UpdateFadeIn()
    {
        Color tempColor = fadeImage.color;

        while (tempColor.a > 0.0f)
        {
            tempColor.a -= Time.deltaTime / fadeSpeed;
            fadeImage.color = tempColor;
            yield return null;
        }

        fadeImage.color = tempColor;
        fadeImage.gameObject.SetActive(false);
        End();
    }

    private IEnumerator UpdateFade(MonoBehaviour monoBehaviour, float fadeDuration)
    {
        yield return curCoroutine = monoBehaviour.StartCoroutine(UpdateFadeOut(fadeDuration));
        yield return curCoroutine = monoBehaviour.StartCoroutine(UpdateFadeIn());
    }

    private IEnumerator UpdateFade(MonoBehaviour monoBehaviour, float fadeDuration, Func<IEnumerator> func)
    {
        yield return curCoroutine = monoBehaviour.StartCoroutine(UpdateFadeOut(fadeDuration));
        yield return curCoroutine = monoBehaviour.StartCoroutine(func());
        yield return curCoroutine = monoBehaviour.StartCoroutine(UpdateFadeIn());
    }

    private void End()
    {
        curCoroutine = null;
    }
}
