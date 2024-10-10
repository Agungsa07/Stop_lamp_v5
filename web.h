String htmlContent = R"====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>SW LIGHT</title>
    <style>
     body {font-family: Arial, sans-serif;color: #111111;margin: 0;display: flex;align-items: center;justify-content: center;height: 100vh;overflow: hidden;background: linear-gradient( 315deg,rgb(20, 20, 20) 3%,rgb(1, 1, 1) 38%,rgb(39, 39, 39) 68%,rgb(13, 17, 40) 98%);}p{font-size: 13px;padding: 0px;margin: 10px 0px 5px;}span{color:#666666;font-size:12px;}.header{position:fixed;top: 0px;left: 0px;width: 100%;text-align:left;height: 55px;padding: 5px 20px 5px;font-weight: 800;font-size: 18px;line-height:22px;background:#111111;color:#ffffff;text-shadow: 0 0 20px #00e5ff, 0 0 30px #9831ff, 0 0 40px #ac59ff;}.header h3{margin:20px 0px 0px;animation: blinker 2s linear infinite;}@keyframes blinker {50% {opacity: 0;}}.header .dropdown {position:inherit;right:20px;top:25px;display: inline-block;text-shadow:none;}.header .dropdown span{font-size:45px;text-shadow:none;color:#ffffff;}.header .dropdown-content {display: none;position: absolute;right: 0px;background-color: #333333;min-width:200px;border-radius:10px;padding:8px;color:#ffffff;font-size: 13px;font-weight: 200;}.header .dropdown-content a{color:#ffffff;}.header .dropdown:hover .dropdown-content {display: block;}.container{position: relative;}.menu-content{padding: 0px;margin: 0px;display: flex;align-items: center;justify-content: center;}.menu-content button{position: relative;background:#111111;color: #ffffff;display: inline-block;padding: 5px;font-weight: 600;cursor: pointer;border-radius:10px;width:110px;text-align: center;margin:10px 5px;border:solid 2px #111111;}.menu-content button span{font-size: 30px;}.menu-content button:hover, .menu-content button:active{border:solid 2px #00d4ff;}.modal {width: 100%;max-width: 100%;margin: 0 auto;padding: 0px 0px 30px;position: absolute;top: 50%;left: 50%;transform: translate(-50%, -50%);background-color:#ffffff;border: 1px solid #ddd;border-radius: 15px;z-index: +999999;}.modal-title{position: relative;padding: 10px 10px;height: 20px;margin-bottom: 5px;font-size: 13px;font-weight: 600;}.close {position: absolute;right:10px;top: 6px;padding: 0.3rem 0.5rem;background: #eee;border-radius: 50%;cursor:pointer;}.modal .modal-body{padding:10px 15px;max-height: 430px;overflow: auto;}input[type=text], select {width: 100%;padding: 8px 10px;margin: 8px 0 8px;display: inline-block;border: 1px solid #ccc;box-sizing: border-box;border-radius:20px;}input[type="range"] {appearance: none;width: 100%;cursor: pointer;outline: none;overflow: hidden;border-radius: 16px;}input[type="range"]::-webkit-slider-runnable-track {height: 15px;background: #ccc;border-radius: 16px;}input[type="checkbox"] {width: 1.5em;height: 1.5em;margin-right: 0.65rem;}.checkbox-group {display:block;margin-top:10px;}.checkbox {margin-bottom:2px;display: flex;background: #eeeeee;padding: 5px;border-radius: 15px;}button{background-image: linear-gradient(to right top, #000000, #101010, #1a1a1a, #242424, #2e2e2e);color: #ffffff;border:0px;padding: 13px 35px;font-weight: 600;cursor: pointer;border-radius:20px;text-align: center;margin-top:5px;}.hidden {display: none;}.credits{position:absolute;bottom: 0px;left: 0px;width: 100%;text-align: center;padding: 20px 0px 20px 0px;color:#666666;font-size: 14px;}.credits a{color:#666666;}   
        @media (max-width: 500px) {
            .menu-content button {width: 100px;}
        }
  </style>
    
</head>
<body>
<div class="header"><h3>ASA_StopLamp</h3><div class="dropdown"><span>≡</span><div class="dropdown-content"><b>Stoplamp v.5</b><br>www.agungsa07.github.io Layanan pembuatan website dan aplikasi<br>Tiktok :<a href="">@agungsaepul_a</a><br>Ig : @agungsaepul_a</div></div></div><div class="container"><div class="menu-content"><button class="btn-modal-text"><span>🧾️</span><p>Text</p></button><button class="btn-modal-custom"><span>💡</span><p>Custom</p></button><button class="btn-modal-combo"><span>🔆</span><p>Combo</p></button></div><div class="menu-content"><form action="/message" method="post"><input type="hidden" name="radio" value="1"><button type="submit"><span>🎥</span><p>Animasi</p></button></form><button class="btn-modal-setting"><span>🔧</span><p>Setting</p></button></div><div class="overlay hidden"></div><div class="modal modal-text hidden"><div class="modal-title">Running Text<span class="close close-modal-text">⨉</span></div><div class="modal-body"><form action="/message" method="post"><input type="hidden" name="radio" value="2"> <input type="text" name="text1" placeholder="Text 1"> <input type="text" name="text2" placeholder="Text 2"> <input type="text" name="text3" placeholder="Text 3"><button type="submit">Submit</button></form></div></div><div class="modal modal-custom hidden"><div class="modal-title">Custom<span class="close close-modal-custom">⨉</span></div><div class="modal-body"><form action="/message" method="post"><input type="hidden" name="radio" value="4"> <input type="text" name="text1" placeholder="Text 1"> <input type="text" name="text2" placeholder="Text 2"> <input type="text" name="text3" placeholder="Text 3"><div class="checkbox-group"><p>Animasi</p><label class="checkbox"><input type="checkbox" name="animation1" value="true">GraphicMidline2</label><label class="checkbox"><input type="checkbox" name="animation2" value="true">GraphicScanner</label><label class="checkbox"><input type="checkbox" name="animation3" value="true">GraphicRandom</label><label class="checkbox"><input type="checkbox" name="animation4" value="true">GraphicSpectrum1</label><label class="checkbox"><input type="checkbox" name="animation5" value="true">GraphicHeartbeat</label><label class="checkbox"><input type="checkbox" name="animation6" value="true">GraphicHearts</label><label class="checkbox"><input type="checkbox" name="animation7" value="true">GraphicEyes</label><label class="checkbox"><input type="checkbox" name="animation8" value="true">GraphicBounceBall</label><label class="checkbox"><input type="checkbox" name="animation9" value="true">GaphicScroller</label><label class="checkbox"><input type="checkbox" name="animation10" value="true">GraphicWiper</label><label class="checkbox"><input type="checkbox" name="animation11" value="true">GraphicInvader</label><label class="checkbox"><input type="checkbox" name="animation12" value="true">GraphicPacman</label><label class="checkbox"><input type="checkbox" name="animation13" value="true">GraphicSpectrum2</label><label class="checkbox"><input type="checkbox" name="animation14" value="true">GraphicSinewave</label><label class="checkbox"><input type="checkbox" name="animation15" value="true">Animation 15</label><label class="checkbox"><input type="checkbox" name="animation16" value="true">Animation 16</label><label class="checkbox"><input type="checkbox" name="animation17" value="true">Animation 17</label><label class="checkbox"><input type="checkbox" name="animation18" value="true">Animation 18</label><label class="checkbox"><input type="checkbox" name="animation19" value="true">Animation 19</label><label class="checkbox"><input type="checkbox" name="animation20" value="true">Animation 20</label><label class="checkbox"><input type="checkbox" name="animation21" value="true">Animation 21</label><label class="checkbox"><input type="checkbox" name="animation22" value="true">Animation 22</label><label class="checkbox"><input type="checkbox" name="animation23" value="true">Animation 23</label><label class="checkbox"><input type="checkbox" name="animation24" value="true">Bullseye</label><label class="checkbox"><input type="checkbox" name="animation25" value="true">CustomWaveAnimation</label><label class="checkbox"><input type="checkbox" name="animation26" value="true">AlternateWaveAnimation</label><label class="checkbox"><input type="checkbox" name="animation27" value="true">OppositeWaveAnimation</label><label class="checkbox"><input type="checkbox" name="animation28" value="true">WaveAnimation</label><label class="checkbox"><input type="checkbox" name="animation29" value="true">CircleWaveAnimation</label></div><button type="submit">Submit</button></form></div></div><div class="modal modal-combo hidden"><div class="modal-title">Combo<span class="close close-modal-combo">⨉</span></div><div class="modal-body"><form action="/message" method="post"><input type="hidden" name="radio" value="3"><p>Combo + Full Animation</p><input type="text" name="text1" placeholder="Text 1"> <input type="text" name="text2" placeholder="Text 2"> <input type="text" name="text3" placeholder="Text 3"><button type="submit">Submit</button></form></div></div><div class="modal modal-setting hidden"><div class="modal-title">Setting<span class="close close-modal-setting">⨉</span></div><div class="modal-body"><form action="/message" method="post"><input type="hidden" name="radio" value="5"><p>Font</p><select id="rem-select" style="width:100%" name="font"><option value="1">Font1</option><option value="2">Font2</option><option value="3">Font3</option><option value="4">Font4</option><option value="5">Font5</option><option value="6">Font6</option><option value="7">Font7</option><option value="8">Font8</option><option value="9">Font9</option><option value="10">Font10</option><option value="11">Font11</option></select><p>Brightness</p><input type="range" class="durasi-slider" name="bright" min="1" max="15" value="15"><span class="durasi-value">15</span><p>Durasi</p><input type="range" class="durasi-slider" name="durasi" min="10" max="60" value="30"><span class="durasi-value">30</span><p>Rem</p><select id="rem-select" style="width:100%" name="rem"><option value="1">REM 1</option><option value="2">REM 2</option><option value="3">REM 3</option><option value="4">REM 4</option><option value="5">No Animasi</option></select><button type="submit">Submit</button></form></div></div></div><div class="credits">Credits : <a href="" class="credits_a" target="_blank"><span class="credits_span">@ASA_Project.id</span></a></div>
    <script>
        const durasiSliders = document.querySelectorAll(".durasi-slider");
        const durasiValueDisplays = document.querySelectorAll(".durasi-value");

        durasiSliders.forEach((slider, index) => {
            slider.addEventListener("input", function() {
                const newValue = slider.value;
                durasiValueDisplays[index].textContent = newValue;
            });
        });

        const overlay = document.querySelector(".overlay");
        var btn_modal_text = document.querySelector(".btn-modal-text");
        var modal_text = document.querySelector(".modal-text");
        var close_modal_text = document.querySelector(".close-modal-text");

        var btn_modal_custom = document.querySelector(".btn-modal-custom");
        var modal_custom = document.querySelector(".modal-custom");
        var close_modal_custom = document.querySelector(".close-modal-custom");

        var btn_modal_combo = document.querySelector(".btn-modal-combo");
        var modal_combo = document.querySelector(".modal-combo");
        var close_modal_combo = document.querySelector(".close-modal-combo");

        var btn_modal_setting = document.querySelector(".btn-modal-setting");
        var modal_setting = document.querySelector(".modal-setting");
        var close_modal_setting = document.querySelector(".close-modal-setting");

        btn_modal_text.addEventListener('click', () => {
            modal_text.classList.remove("hidden");
        });

        close_modal_text.addEventListener('click', () => {
            modal_text.classList.add("hidden");
        });

        /**Modal CUstom */
        btn_modal_custom.addEventListener('click', () => {
            modal_custom.classList.remove("hidden");
        });

        close_modal_custom.addEventListener('click', () => {
            modal_custom.classList.add("hidden");
        });

        
        /**Modal Combo */
        btn_modal_combo.addEventListener('click', () => {
            modal_combo.classList.remove("hidden");
        });

        close_modal_combo.addEventListener('click', () => {
            modal_combo.classList.add("hidden");
        });

        /**Modal Setting */
        btn_modal_setting.addEventListener('click', () => {
            modal_setting.classList.remove("hidden");
        });

        close_modal_setting.addEventListener('click', () => {
            modal_setting.classList.add("hidden");
        });
    </script>
</body>
</html>
)====";
