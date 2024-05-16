<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Str;
use Illuminate\Support\Facades\DB;
use Illuminate\Support\Facades\Storage;


class UserController extends Controller
{
    //
    public function userprofile(Request $request)
    {   
        $token = $request->header('Authorization');
        if (Str::startsWith($token, 'Bearer ')) {
            $token = Str::substr($token, 7);
        }
        $user = auth()->user();
        if (!$user) {
            return response()->json(['error' => 'Unauthorized'], 487);
        }
        $people_num = DB::table('users')->count();
        $topic_num = DB::table('topics')->count();
        return response()->json(['user' => $user, 'people_num' => $people_num, 'topic_num' => $topic_num], 200);
    }

    public function updateimg(Request $request)
    {   
        $user = auth()->user();
        if (!$user) {
            return response()->json(['error' => 'Unauthorized'], 487);
        }
        // $this->validate($request, [
        //     'image' => 'required', // 确保接收到图片数据
        //     'username' => 'required',
        //     'password' => 'required'
        // ]);
        // return '48763';
        $mail = DB::table('users')->where('username', $request->username)->value('email');
        $credentials = ['email' => $mail, 'password' => $request->password];
        if (!auth()->attempt($credentials)) {
            return response()->json(['error' => 'Unauthorized'], 401);
        }

        $image_parts = explode(";base64,", $request->image);
        $image_type_aux = explode("image/", $image_parts[0]);
        $image_type = $image_type_aux[1];
        $image_base64 = base64_decode($image_parts[1]);
    
        $file_name = 'image_' . uniqid() . '.' . $image_type;
        Storage::disk('public')->put("images/{$file_name}", $image_base64);
        $path = "storage/images/{$file_name}";
        DB::table('users')->where('username', $request->username)->update(['photo' => $path]);
        return response()->json(['status' => 'success'], 200);
    }

    public function getowntopics(Request $request)
    {   
        $user = auth()->user();
        if (!$user) {
            return response()->json(['error' => 'Unauthorized'], 487);
        }
        $topics = DB::table('topics')->where('owner', $user->id)->get();
        foreach ($topics as $topic) {
            $topic->options = DB::table('poll_options')->where('topic_id', $topic->id)->pluck('item_name');
        }
        return response()->json(['topics' => $topics], 200);
    }
}

