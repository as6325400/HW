<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Str;
use Illuminate\Support\Facades\DB;

class VoteController extends Controller
{
    public function createvote(Request $request)
    {   
        $token = $request->header('Authorization');
        if (Str::startsWith($token, 'Bearer ')) {
            $token = Str::substr($token, 7);
        }
        $user = auth()->user();
        if (!$user) {
            return response()->json(['error' => 'Unauthorized'], 487);
        }
        $topic = $request->input('topic');
        $title = $request->input('title');
        if(DB::table('topics')->where('topic_name', $topic)->where('title', $title)->exists()){
            return response()->json(['error' => 'The vote has already existed'], 488);
        }
        $options = $request->input('options');
        DB::table('topics')->insert([
            'topic_name' => $topic,
            'title' => $title,
            'owner' => $user['id'],
        ]);
        $topic_id = DB::table('topics')->where('topic_name', $topic)->where('title', $title)->value('id');
        foreach ($options as $option) {
            DB::table('poll_options')->insert([
                'topic_id' => $topic_id,
                'item_name' => $option,
            ]);
        }
        return response()->json(['topic_name' => $topic, 'title' => $title,
            'owner' => $user['username'], 'options' => $options
        ], 200);
    }

    public function deletevote(Request $request)
    {
        $token = $request->header('Authorization');
        if (Str::startsWith($token, 'Bearer ')) {
            $token = Str::substr($token, 7);
        }
        $user = auth()->user();
        if (!$user) {
            return response()->json(['error' => 'Unauthorized'], 487);
        }
        $topic = $request->input('topic');
        $title = $request->input('title');
        $topic_id = DB::table('topics')->where('topic_name', $topic)->where('title', $title)->value('id');
        DB::table('topics')->where('topic_name', $topic)->where('title', $title)->delete();
        DB::table('poll_options')->where('topic_id', $topic_id)->delete();
        return response()->json(['topic_name' => $topic, 'title' => $title,
            'owner' => $user['username']
        ], 200);
    }

    public function gettime(Request $request)
    {
        $topic = $request->input('topic');
        $title = $request->input('title');
        $time = DB::table('topics')->where('topic_name', $topic)->where('title', $title)->value('time');

        return response()->json(['topic_name' => $topic, 'title' => $title,
            'time' => $time
        ], 200);
    }

    public function getallvotes(Request $request)
    {   
        $topics = DB::table('topics')->get();
        foreach ($topics as $topic) {
            $topic->options = DB::table('poll_options')->where('topic_id', $topic->id)->get();
            $topic->ownerpath = DB::table('users')->where('id', $topic->owner)->value('photo');
            $topic->ownername = DB::table('users')->where('id', $topic->owner)->value('username');
        }
        return response()->json(['topics' => $topics], 200);
    }
}
